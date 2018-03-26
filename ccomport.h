#ifndef CCOMPORT_H
#define CCOMPORT_H

#include <QThread>
#include <QObject>
#include "cparam.h"
#include <windows.h>
#include <setupapi.h>
//#include "CStackFourth.h"

class CComPort : public QThread
{
    Q_OBJECT
public:
    enum eComPortState {cpsNoState, cpsConnect, cpsConnect1, cpsConnect2, cpsReload, cpsDisConnect, cpsError};
private:
    unsigned number_port, new_number_port;
    unsigned second, new_second;
    eComPortState state;
    HANDLE hCom;
    unsigned st_packet, bad_second;

    unsigned long a, side, def, dat, koord, pm1, pm2, koordm1, koordm2, koordm3, koordm4;
    bool def_absolut;
    long skoord, koord_old;
    unsigned round;
    int height_koleso;
    unsigned kind_work, new_kind_work;// 1 - scan; 2 - motor up; 3 - motor down
    unsigned mes1, mes2;
    unsigned old_mes1, old_mes2;
    unsigned hl, hr;
    bool stoped;

    void Connect();
    void DisConnect(eComPortState new_state);
    bool IsNewNumberPort(const bool &set = true);
    bool IsNewSecond();
    void SetState(const eComPortState &s) {state = s; emit NewState(state);}
    bool InByte(unsigned char& byte);
    bool OutByte(unsigned char byte);

    void Execute();
    unsigned OfficeFunction(bool kind = false);
    bool CommandGetState();
    bool CommandSetAuto();
    bool CommandSetHand();
    bool SetMotor(const int n1, const int v1, const int n2, const int v2);
    bool CommandSetMotor(const unsigned number, const unsigned mm);
    bool CommandSetTuning(int side, int number);
    bool CommandResetKoordinat();
    bool WaitForEndDefect(int min_kol = 100);
    bool SetMotorUp();
    bool SetMotorDown();
    void OnStoped(const unsigned n1, const unsigned n2);

public:
    CComPort(QObject *parent = 0);
    ~CComPort();

    void run();    
    void SetNumberPort(const unsigned &n) {new_number_port = n;}
    void SetNewSecond() {new_second ++;}
    void Begin(unsigned new_kw, unsigned h);
    void Stop(const bool only_stoped = false);

signals:
    void NewState(unsigned s);
    void NewBlockState(unsigned type, unsigned w, unsigned l);//0-end; 8-defect; 1-mes1; 2-mes2;
        //0x10-ошибка подвода левая;

public slots:

};
#endif // CCOMPORT_H
