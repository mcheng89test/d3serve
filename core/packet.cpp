#include "packet.h"
#include <iostream.h>
#include <sstream>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

void DumpBuffer(unsigned char* buffer, long len) {
    printf("<< Client[size=%i]: ", len);
    for (int i=0; i<len; i++)
        printf("%02X ", buffer[i]);
    printf("\n");
}
Packet::Packet() {
    valid = true;
    null = false;
    Payload = 0;
}
Packet::Packet(byte ServiceId, uint32 MethodId, uint16 RequestId, google::protobuf::Message *message) {
    valid = true;
    null = false;
    this->ServiceId = ServiceId;
    this->MethodId = MethodId;
    this->RequestId = RequestId;
    this->PayloadLength = message->ByteSize();
    this->Payload = new byte[message->ByteSize()];
    message->SerializeToArray(this->Payload, message->ByteSize());
}

Packet Packet::Read(ClientService client) {
    Packet p;
    byte header[6];
    long len = client.socket->Receive(header, 6);
    
    if (len > 0) {
        google::protobuf::io::CodedInputStream coded_input(header, (int)len);
        coded_input.ReadRaw(&p.ServiceId, 1);
        coded_input.ReadVarint32(&p.MethodId);
        byte requestIdTemp[2];
        coded_input.ReadRaw(requestIdTemp, 2);
        p.RequestId =  requestIdTemp[0] | (requestIdTemp[1] << 8);
        if (p.ServiceId != 0xfe) coded_input.ReadVarint64(&p.Unknown);
        coded_input.ReadVarint32(&p.PayloadLength);
        if (p.PayloadLength > 0) {
            p.Payload = new byte[p.PayloadLength];
            //coded_input.ReadRaw(p.Payload, p.PayloadLength);
            client.socket->Receive(p.Payload, p.PayloadLength);
        }
    } else p.valid = false;
    return p;
}

int Packet::Write(ClientService client) {
    if (null/*null packet*/)
        return 0;
    byte buf[6];
    google::protobuf::io::ArrayOutputStream raw_output(buf, 1024);
    google::protobuf::io::CodedOutputStream coded_output(&raw_output);
    coded_output.WriteRaw((void*)&ServiceId, 1);
    coded_output.WriteVarint32(MethodId);
    byte requestIdTemp[2];
    requestIdTemp[0] = (byte)(RequestId & 0xff);
    requestIdTemp[1] = (byte)(RequestId >> 8);
    coded_output.WriteRaw(requestIdTemp, 2);
    if (ServiceId != 0xfe) coded_output.WriteVarint64(Unknown);
    coded_output.WriteVarint32(PayloadLength);
    client.socket->Send(buf, coded_output.ByteCount());
    //DumpBuffer(buf, coded_output.ByteCount());
    if (PayloadLength > 0) {
        client.socket->Send(Payload, PayloadLength);
        //DumpBuffer(Payload, PayloadLength);
    }
    return 0;
}

Packet Packet::getNullPacket() {
    Packet packetOut;
    packetOut.null = true;
    return packetOut;
}
Packet Packet::getInvalidPacket() {
    Packet packetOut;
    packetOut.valid = false;
    return packetOut;
}

bool Packet::isValid() {
    return valid;
}

std::string Packet::toString() {
    std::stringstream ss;
    ss << "[S]: " << (int)ServiceId << ", [M]: " << MethodId << ", [R]: " << RequestId << ", [L]: " << PayloadLength;
    return ss.str();
}
