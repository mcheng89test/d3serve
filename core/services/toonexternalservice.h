/*
 Diablo 3 Server Emulator
 Copyright (C) 2011 D3Sharp (https://github.com/raistlinthewiz/d3sharp)
 
 Ported to C++ by mcheng89
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef D3Serve_toonexternalservice_h
#define D3Serve_toonexternalservice_h

#include "../service.h"

class ToonExternalService: public CoreService {
public:
    ToonExternalService();
    Packet CallMethod(ClientService *client, Packet packetIn);
private:
    Packet ToonList(ClientService *client, Packet packetIn);
    Packet SelectToon(ClientService *client, Packet packetIn);
    Packet CreateToon(ClientService *client, Packet packetIn);
    Packet DeleteToon(ClientService *client, Packet packetIn);
};

#endif
