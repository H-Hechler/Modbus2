
#ifndef NTPTime_H_
#define NTPTime_H_
unsigned int localPort = 2390; // local port to listen for UDP packets
//IPAddress timeServer(162, 159, 200, 123); // pool.ntp.org NTP server
constexpr auto timeServer { "pool.ntp.org" };
const int NTP_PACKET_SIZE = 48; // NTP timestamp is in the first 48 bytes of the message
byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming and outgoing packets
// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
constexpr unsigned long printInterval { 1000 };
unsigned long printNow {};

void setNtpTime();
unsigned long sendNTPpacket(const char * address);
void releaseNTP();
#endif