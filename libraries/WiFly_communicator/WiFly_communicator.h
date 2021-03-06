#ifndef __WIFLY_H__
#define __WIFLY_H__

#include <Arduino.h>
#include <Stream.h>

#define DEFAULT_WAIT_RESPONSE_TIME      1500        // 1000ms
#define DEFAULT_BAUDRATE                19200
#define MAX_CMD_LEN                     32
#define MAX_TRY_JOIN                    3

// Auth Modes for Network Authentication
// See WiFly manual for details
#define WIFLY_AUTH_OPEN        0    // Open (default)  
#define WIFLY_AUTH_WEP         1    // WEP-128
#define WIFLY_AUTH_WPA1        2    // WPA1
#define WIFLY_AUTH_WPA1_2      3    // Mixed-mode WPA1 and WPA2-PSK
#define WIFLY_AUTH_WPA2_PSK    4    // WPA2-PSK
#define WIFLY_AUTH_ADHOC       6    // Ad-hoc, join any Ad-hoc network

class WiFly : public Stream
{
  public:
    WiFly(Stream *);

    size_t write(uint8_t);
    size_t write(const uint8_t *, size_t);
    int available();
    int read();
    int peek();
    void flush();
	
	static WiFly* getInstance() {
	   return instance;
	}
    
    boolean init();
    boolean reset();
    boolean reboot();
    boolean runWebApp();
    //boolean scan();
    
    boolean join(const char *ssid, const char *phrase = NULL, int auth = WIFLY_AUTH_OPEN);
    boolean leave();
    
    boolean connect(const char *host, uint16_t port, int timeout = DEFAULT_WAIT_RESPONSE_TIME);

    boolean staticIP(const char *ip, const char *mask, const char *gateway);
    
    int send(const char *data, int timeout = DEFAULT_WAIT_RESPONSE_TIME);
    int send(const uint8_t *data, int len, int timeout = DEFAULT_WAIT_RESPONSE_TIME);
    int receive(uint8_t *buf, int len, int timeout = DEFAULT_WAIT_RESPONSE_TIME);
    
    boolean ask(const char *q, const char *a, int timeout = DEFAULT_WAIT_RESPONSE_TIME);
    boolean sendCommand(const char *cmd, const char *ack = NULL, int timeout = DEFAULT_WAIT_RESPONSE_TIME);
  
    boolean commandMode();
    boolean dataMode();
    
    void clear();

    float version();
    
  private:
    static WiFly*  instance;

    Stream* serial;
	
    boolean command_mode;
    boolean associated;
    uint8_t dhcp;
    
};

#endif // __WIFLY_H__

