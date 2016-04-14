#ifndef __USEFULDATAPACKET_HPP__
#define __USEFULDATAPACKET_HPP__

/*
class usefulDataPacket
{
private:
    string _message;
    unsigned int _messageSize;
    string _checksum;

public:
    usefulDataPacket(string& message)
    {
        _message = message;
        _messageSize = sizeof(message);
        _checksum = "checksum";
    }

    usefulDataPacket(string& message, unsigned int messageSize, string& checksum)
    {
        _message = message;
        _messageSize = messageSize;
        _checksum = checksum;
    }

    string getMessage() const
    {
        return _message;
    }
    void setMessage(string message)
    {
        _message = message;
    }

    unsigned int getMessageSize() const
    {
        return _messageSize;
    }
    void setMessage(unsigned int messageSize)
    {
        _messageSize = messageSize;
    }

    string getChecksum() const
    {
        return _checksum;
    }
    void setChecksum(string checksum)
    {
        _checksum = checksum;
    }
};
*/

class usefulDataPacket
{
private:
    char _message[256];
    unsigned int _messageSize;
    char _checksum[512];

public:
    usefulDataPacket(string& message)
    {
        strcpy(_message, message.c_str());
        _messageSize = sizeof(_message);
        char checksum[] = "checksum";
        strcpy(_checksum, checksum);
    }

    usefulDataPacket(string& message, unsigned int messageSize, string& checksum)
    {
        strcpy(_message, message.c_str());
        _messageSize = messageSize;
        strcpy(_checksum, checksum.c_str());
    }

    char* getMessage()
    {
        return _message;
    }
    void setMessage(string message)
    {
        strcpy(_message, message.c_str());
    }

    unsigned int getMessageSize() const
    {
        return _messageSize;
    }
    void setMessage(unsigned int messageSize)
    {
        _messageSize = messageSize;
    }

    char* getChecksum()
    {
        return _checksum;
    }
    void setChecksum(string checksum)
    {
        strcpy(_checksum, checksum.c_str());
    }
};

#endif // __USEFULDATAPACKET_HPP__

