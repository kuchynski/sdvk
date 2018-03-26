#include "ccomport.h"

CComPort::CComPort(QObject *parent) : QThread(parent),
    number_port(0), new_number_port(0), hCom(0), height_koleso(0), kind_work(0), new_kind_work(0),
    hl(10), hr(10), stoped(false)
{
}
CComPort::~CComPort()
{
    DisConnect(cpsDisConnect);
}

void CComPort::run()
{
    SetState(cpsNoState);
    bool ok = false;
    round = 0;
    while(1)
    {
        if(OfficeFunction(true) == 2)
        {
           // OnStoped(0x10, 0);
            DisConnect(cpsDisConnect);
            if(number_port == 100)//завершить поток
                break;
            ok = false;
            Connect();
        }
        if((state == cpsConnect) || (state == cpsConnect1) || (state == cpsConnect2))
        {
            CommandGetState();
            if(new_kind_work)
            {
                kind_work = new_kind_work;
                switch(kind_work)
                {
                    case 1:
                            Execute();
                            SetMotorDown();
                            break;
                    case 2:
                            SetMotorUp();
                            break;
                    case 3:
                            SetMotorDown();
                            break;
                }
                CommandSetHand();
                if(kind_work == new_kind_work)
                    new_kind_work = 0;
                kind_work = 0;
            }
        }
        else
            msleep(100);
    }
}
void CComPort::Begin(unsigned new_kw, unsigned h)
{
    new_kind_work = new_kw;
    if(h)
        height_koleso = h;
}
void CComPort::Stop(const bool only_stoped)
{
    if(!only_stoped)
        new_kind_work = 0;
    stoped = false;
}
unsigned CComPort::OfficeFunction(bool kind)
{
    if(IsNewNumberPort(kind))
        return 2;
    if((state == cpsConnect) || (state == cpsConnect1) || (state == cpsConnect2))
    {
        if(IsNewSecond())
        {
            if(!st_packet && (number_port < 10))
            {
                bad_second ++;
                SetState(cpsConnect2);
            }
            else
            {
                bad_second = 0;
                SetState(cpsConnect1);
            }
            st_packet = 0;
        }
    }
    return (kind_work != new_kind_work)? 1 : 0;
}
void CComPort::OnStoped(const unsigned n1, const unsigned n2)
{
    stoped = true;
    emit NewBlockState(n1, n2, n2);
    while(stoped)
    {
        if(!CommandGetState())
            msleep(100);
    }
}
void CComPort::Execute()
{
   // sleep(1); emit NewBlockState(0, mes1, mes2); return;
    old_mes1 = 0xFFFFFFFF;
    old_mes2 = 0xFFFFFFFF;
    const unsigned height_ = height_koleso;
    CommandSetAuto();
    int max_coordinate = param.GetRast(0);

    koord_old = skoord;
    const unsigned kol_scan = (height_ > 40)? 1 : 0;
    for(round = 0; round <= kol_scan; round ++)
    {
        unsigned v = height_ - round * kol_scan * 5;
        if(!SetMotor(1, v, 2, v))
            return;
        if(round == 0)
        {
            CommandSetTuning(0, 1);
            if(!WaitForEndDefect(100))
                return;
            hl = 10;
            hr = 10;
            CommandSetMotor(3, hl);
            do
            {
                if(OfficeFunction()) return;
                CommandGetState();
                if(def_absolut)
                {
                    hl = koordm3;
                    CommandSetMotor(3, hl);
                    break;
                }
                koord_old = skoord;
            }while(koordm3 != hl);
            if(!def_absolut)
                OnStoped(0x10, 0);
            if(OfficeFunction()) return;
            CommandSetTuning(1, 1);
            if(!WaitForEndDefect(100))
                return;
            CommandSetMotor(4, hr);
            do
            {
                if(OfficeFunction()) return;
                CommandGetState();
                if(def_absolut)
                {
                    hr = koordm4;
                    CommandSetMotor(4, hr);
                }
                koord_old = skoord;
            }while(koordm4 != hr);
            if(!def_absolut)
                OnStoped(0x10, 1);
            if(OfficeFunction()) return;
        }

        while(round)
        {
            koord_old = skoord;
            if(OfficeFunction()) return;
            if(CommandGetState())
                if(((skoord >= max_coordinate) || (skoord <= -max_coordinate)) && (koord_old != skoord))
                    break;
        }
        if(OfficeFunction()) return;
        //????????????
        for(int s = 0; s <= 1; s++)
        {
            for(int i = 0; i < 9; i++)
            {
                if(param.GetEnabledDat(i, round))
                {
                    CommandSetTuning(s, i);
                    CommandResetKoordinat();
                    if(!WaitForEndDefect(param.GetRast(2) * 10))
                        return;
                  //  koord_old = 951254;
                    while(1)
                    {
                        if(OfficeFunction()) return;
                        if(CommandGetState())
                        {
                            if(((koord_old != skoord) && (skoord != 0)) || def)//(!d_old && def))
                                emit NewBlockState(0x08, mes1, mes2);
                            if(((skoord >= max_coordinate) || (skoord <= -max_coordinate)) && (koord_old != skoord))
                                break;
                            koord_old = skoord;
                           // d_old = def;
                        }
                    }
                }
            }
        }
        CommandResetKoordinat();
    }
    round = 0;
    emit NewBlockState(0, mes1, mes2);
    if(!kol_scan)
    {
        unsigned kol_press = 0;
        for(unsigned i = 0; i < 8; i ++)
            if(param.GetEnabledDat(0, 1))
                kol_press += 2;
        for(unsigned i = 0; i < kol_press; i ++)
        {
            CommandSetTuning(0, 0);
            msleep(1000);
        }
    }
}
bool CComPort::SetMotorUp()
{
    const unsigned height_ = height_koleso;
    if(!SetMotor(1, height_, 2, height_))
        return false;
    CommandSetTuning(0, 1);
    if(!WaitForEndDefect(100))
        return false;
    hl = 10;
    hr = 10;
    CommandSetMotor(3, hl);
    do
    {
        if(OfficeFunction()) return false;
        CommandGetState();
        if(def_absolut)
        {
            hl = koordm3;
            CommandSetMotor(3, hl);
            break;
        }
       // koord_old = skoord;
    }while(koordm3 != hl);
    CommandSetTuning(1, 1);
    if(!WaitForEndDefect(100))
        return false;
    CommandSetMotor(4, hr);
    do
    {
        if(OfficeFunction()) return false;
        CommandGetState();
        if(def_absolut)
        {
            hr = koordm4;
            CommandSetMotor(4, hr);
        }
       // koord_old = skoord;
    }while(koordm4 != hr);
    return true;
}
bool CComPort::SetMotorDown()
{
    //if(!SetMotor(1, param.GetRast(1), 2, param.GetRast(1)))
      //  return false;
    SetMotor(1, param.GetRast(1), 2, param.GetRast(1));
    return SetMotor(3, param.GetRast(3), 4, param.GetRast(3));
}
void CComPort::Connect()
{
    if(!number_port)
    {
        SetState(cpsNoState);
        return;
    }
    int ok = false;
    if(number_port < 10)
    {
        do{
            WCHAR name[6] = {'C', 'O', 'M', '0' + number_port};
            COMMCONFIG ComCfg;
            COMMTIMEOUTS CommTimeouts;
            BOOL fSuccess;

            ComCfg.dwSize = sizeof(COMMCONFIG);
            ComCfg.wVersion = 1;
            ComCfg.dwProviderSubType = PST_RS232;
            ComCfg.dwProviderOffset = 0;
            ComCfg.dwProviderSize = 0;
            //t = (kol*ReadTotalTimeoutMultiplier + ReadTotalTimeoutConstant)
            CommTimeouts.ReadIntervalTimeout = 10;//между двумя символами
            CommTimeouts.ReadTotalTimeoutMultiplier = 10;
            CommTimeouts.ReadTotalTimeoutConstant = 10;
            CommTimeouts.WriteTotalTimeoutMultiplier = 10;
            CommTimeouts.WriteTotalTimeoutConstant = 10;
            SetDefaultCommConfig(name, &ComCfg, sizeof(ComCfg));
            hCom = CreateFile(name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
            if(hCom == INVALID_HANDLE_VALUE)
                break;
            GetCommState(hCom, &ComCfg.dcb);
            ComCfg.dcb.ByteSize = 8;
            ComCfg.dcb.Parity = NOPARITY;
            ComCfg.dcb.StopBits = ONESTOPBIT;
            ComCfg.dcb.BaudRate = 19200;
            ComCfg.dcb.fRtsControl = RTS_CONTROL_DISABLE;
            SetCommState(hCom, &ComCfg.dcb);
            SetCommTimeouts(hCom, &CommTimeouts);
           // SetupComm(hCom, 100000, 0);
           // PurgeComm(hCom, PURGE_RXCLEAR);
            ok = true;
        }while(0);

    }
    else
    {
       //f = fopen("test.bin", "rb");
       // ok = (f)? 1 : 0;
    }
    if(!ok)
    {
        CloseHandle(hCom);
        hCom = 0;
        SetState(cpsError);
        return;
    }
    st_packet = 0;
    bad_second = 0;
    SetState(cpsConnect);
    return;
}
void CComPort::DisConnect(eComPortState new_state)
{
    if(hCom)
    {
        CloseHandle(hCom);
        hCom = 0;
    }
    SetState(new_state);
    return;
}
bool CComPort::IsNewNumberPort(const bool &set)
{
    if(new_number_port == number_port)
        return false;
    if(set)
    {
        if(new_number_port > 100)
            new_number_port -= 100;
        number_port = new_number_port;
    }
    return true;
}
bool CComPort::IsNewSecond()
{
    if(new_second == second)
        return false;
    second = new_second;
    return true;
}
//---------------------------------------------------------------------------
bool CComPort::InByte(unsigned char& byte)
{
    DWORD n = 1;
    bool ret = ReadFile(hCom, &byte, n, &n, NULL);
    return (ret && n == 1);
}
bool CComPort::OutByte(unsigned char byte)
{
    DWORD n = 1;
    bool ret = WriteFile(hCom, &byte, n, &n, NULL);
    return (ret && n == 1);
}
bool CComPort::CommandGetState()
{
  /*  koord = (koord < param.GetRast(0))? koord + 1 : 0; def = (def == 0x55)? 0 : 0x55; mes2 = (def << 24) + koord;
    side = 0; dat = 0;  round = 1; mes1 = (side << 16) + (dat << 8) + round;
    msleep(30);
    unsigned t = (mes1 != old_mes1)? 1 : 0;
    if(mes2 != old_mes2)
        t += 2;
    if(t)
    {
        emit NewBlockState(t, mes1, mes2);
        old_mes1 = mes1;
        old_mes2 = mes2;
    }
    return true;*/

    unsigned char b1, b2 = 0;
    while(1)
    {
        if(!InByte(b1))
            return false;
        if((b1 == 0xA1) && (b2 == 0x56))
            break;
        if(OfficeFunction())
            return false;
        b2 = b1;
    }
    if(!InByte(b1)) return false;
    if(!InByte(b2)) return false;
    if(b1 != b2) return false;
    if((b1 & 0xC0) == 0x40)
        side = 0;
    else if((b1 & 0xC0) == 0x80)
        side = 1;
    else return false;
    if((b1 & 0x30) == 0x30)
    { def = 0x55; def_absolut = true;}
    else if((b1 & 0x30) == 0x00)
    { def = 0; def_absolut = false;}
    else return false;

    dat = ((unsigned long)b1) & 0x000000F;
    if(!InByte(b1)) return false;
    if(!InByte(b2)) return false;
    if(b1 != b2) return false;
    koord = (unsigned long)b1;
    if(!InByte(b1)) return false;
    if(!InByte(b2)) return false;
    if(b1 != b2) return false;
    koord = (koord << 8) + (unsigned long)b1;
    if(koord & 0x00008000)
        skoord = -(0x0000ffff - koord + 1);
    else
        skoord = koord;

    if(!InByte(b1)) return false;
    koordm1 = (unsigned long)b1;
    if(!InByte(b1)) return false;
    koordm2 = (unsigned long)b1;
    if(!InByte(b1)) return false;
    koordm3 = (unsigned long)b1;
    if(!InByte(b1)) return false;
    koordm4 = (unsigned long)b1;
    if(skoord < 2 && skoord > -2)
        def = 0;
    mes1 = (side << 16) + (dat << 8) + round;
//    mes2 = (koordm2 << 24) + (koordm1 << 16) + koord;
    mes2 = (def << 24) + koord;
    st_packet ++;
    unsigned type = (mes1 != old_mes1)? 1 : 0;
    if(mes2 != old_mes2)
        type += 2;
    if(type)
    {
        emit NewBlockState(type, mes1, mes2);
        old_mes1 = mes1;
        old_mes2 = mes2;
    }
    return true;
}
bool CComPort::CommandSetAuto()
{
    OutByte(0x09);
    return true;
}
bool CComPort::CommandSetHand()
{
    OutByte(0x0A);
    return true;
}
bool CComPort::SetMotor(const int n1, const int v1, const int n2, const int v2)
{
    int km1, km2;
    do
    {
        CommandSetAuto();
        CommandSetMotor(n1, v1);
        CommandSetMotor(n2, v2);
        CommandGetState();
        if(OfficeFunction())
        {
            return false;
        }
     //   koord_old = skoord;
        switch(n1)
        {
            case 1: km1 = koordm1; break;
            case 2: km1 = koordm2; break;
            case 3: km1 = koordm3; break;
            default: km1 = koordm4;
        }
        switch(n2)
        {
            case 1: km2 = koordm1; break;
            case 2: km2 = koordm2; break;
            case 3: km2 = koordm3; break;
            default: km2 = koordm4;
        }
    }while((km1 != v1) || (km2 != v2));
    return true;
}
bool CComPort::CommandSetMotor(const unsigned number, const unsigned mm)
{
    bool ret = true;
    switch(number)
    {
        case 1: OutByte(0x40 + ((unsigned char)(mm-20) & 0x3F)); break;
        case 2: OutByte(0x80 + ((unsigned char)(mm-20) & 0x3F)); break;
        case 3: OutByte(0xC0 + ((unsigned char)(mm-10) & 0x1F)); break;
        case 4: OutByte(0xE0 + ((unsigned char)(mm-10) & 0x1F)); break;
        default: ret = false;
    }
    return ret;
}
bool CComPort::CommandSetTuning(int side, int number)
{
    OutByte(0x10 + ((unsigned char)side & 0x0F));
    msleep(100);
    OutByte(0x20 + ((unsigned char)number & 0x0F));
    return true;
}
bool CComPort::CommandResetKoordinat()
{
    while(1)
    {
        OutByte(0x08);
        if(OfficeFunction()) return false;
        CommandGetState();
        if(skoord == 0)
            break;
    }
    return true;
}
bool CComPort::WaitForEndDefect(int min_kol)
{             //min_kol: = 10 = 0.1 ??? = 2.5 ?????. = 2 ???????
    unsigned long mes1, mes2;
    bool ok = false;
    int max_kol = 200;
    for(; (min_kol > 0) || !ok; min_kol --, max_kol --)
    {
        CommandGetState();
        if(OfficeFunction()) return false;
        if(!def_absolut)
            ok = true;
        if(!max_kol)
            break;
    }
    return true;
}
