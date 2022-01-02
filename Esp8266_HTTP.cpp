#include <Esp8266_HTTP.h>

void Esp::begin(uint32_t baund)
{
  EspSerial.begin(baund);
}

boolean Esp::ready()
{
    EspSerial.println("AT");
    while (!EspSerial.find("OK"))
        EspSerial.println("AT");
    return true;
}

boolean Esp::clientMode()
{
    if (ready())
    {
        EspSerial.println("AT+CWMODE=1");
        while (!EspSerial.find("OK"))
            EspSerial.println("AT+CWMODE=1");
        return true;
    }
    else
        return false;
}

boolean Esp::connect(String ssid, String pass)
{
    if (clientMode())
    {
        EspSerial.println("AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"");
        while (!EspSerial.find("OK"))
            return true;
    }
    else
        return false;
}

boolean Esp::startHttp(String ip, String port)
{
    EspSerial.println("AT+CIPSTART=\"TCP\",\"" + ip + "\"," + port);
    if (EspSerial.find("OK"))
        return true;
    else
        return false;
}

boolean Esp::http(String uri, String method)
{
    String data = method + " /" + uri + "/\r\n\r\n";
    EspSerial.print("AT+CIPSEND=");
    EspSerial.println(data.length() + 2);
   
    if (EspSerial.find(">"))
    {
        EspSerial.println(data);
        while(!EspSerial.find("OK"));
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
