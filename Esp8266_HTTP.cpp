#include <Esp8266_HTTP.h>

char Esp::read()
{
   return EspSerial.read();
}

void Esp::begin(uint32_t baund)
{
    EspSerial.begin(baund);
}

void Esp::listen()
{
    EspSerial.listen();
}

boolean Esp::available()
{
    return EspSerial.available();
}

boolean Esp::ready()
{
    EspSerial.println("AT");
    while (EspSerial.available() > 0 && !EspSerial.find("OK"))
        EspSerial.println("AT");
    return true;
}

boolean Esp::clientMode()
{
    if (ready())
    {
        EspSerial.println("AT+CWMODE=1");
        while (EspSerial.available() > 0 && !EspSerial.find("OK"))
            EspSerial.println("AT+CWMODE=1");
        return true;
    }
    else
        return false;
}

boolean Esp::connect(String ssid, String pass)
{
    EspSerial.listen();
    if (clientMode())
    {
        EspSerial.println("AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"");
        while (EspSerial.available() > 0 && !EspSerial.find("OK"))
            return true;
    }
    else
        return false;
}

boolean Esp::startHttp(String ip, String port)
{
    EspSerial.listen();
    EspSerial.println("AT+CIPSTART=\"TCP\",\"" + ip + "\"," + port);
    if (EspSerial.available() > 0 && EspSerial.find("OK"))
        return true;
    else
        return false;
}

boolean Esp::http(String uri, String method)
{
    String data = method + " /" + uri + "/\r\n\r\n";
    EspSerial.print("AT+CIPSEND=");
    EspSerial.println(data.length() + 2);

    if (EspSerial.available() > 0 && EspSerial.find(">"))
    {
        EspSerial.println(data);
        while (EspSerial.available() > 0 && !EspSerial.find("OK"))
            ;
        return true;
    }
    else
        return false;
}

boolean Esp::closeHttp()
{
    EspSerial.println("AT+CIPCLOSE");
    return true;
}
