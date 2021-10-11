struct
{
    int seqNum;
    int armed;
    int finished;
    char buffer[4];
    //Timing object here
} typedef sentFrame;

struct
{
    int16_t sourceAddress;
    int16_t destAddress;
    int16_t length;
    int16_t checksum;
    char data[4];
    sentFrame frame;
} typedef packet;

struct{     uint8_t   ver_hlen;   /* Header version and length (dwords). */
    uint8_t   service;    /* Service type. */
    uint16_t  length;     /* Length of datagram (bytes). */
    uint16_t  ident;      /* Unique packet identification. */
    uint16_t  fragment;   /* Flags; Fragment offset. */
    uint8_t   timetolive; /* Packet time to live (in network). */
    uint8_t   protocol;   /* Upper level protocol (UDP, TCP). */
    uint16_t  checksum;   /* IP header checksum. */
    uint32_t  src_addr;   /* Source IP address. */
    uint32_t  dest_addr;  /* Destination IP address. */
    
} typedef NetIpHdr;


/*
 * IP Packet
 */
struct
{
    NetIpHdr ipHdr;
    packet  pack;

} typedef NetIpPkt;

void printPacket(packet);
void rewindFile(packet);
void rewindFileIp(NetIpPkt);
void printIpPacket(NetIpPkt);

