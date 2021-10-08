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

void printPacket(packet);
void rewindFile(packet);

