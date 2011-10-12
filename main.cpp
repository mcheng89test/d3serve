/*
 Diablo 3 Server Emulator - DELETE
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

#include "core/service.h"
#include "utils/serversocket.h"
#include <fstream>

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define SERVER_PORT 6666

void HandleClient(ClientSocket c);

int main (int argc, const char * argv[])
{
    std::ifstream dbfile("database.db");
    if (!dbfile) {
        dbfile.close();
        Logger::Error("Could not file database");
        char cCurrentPath[FILENAME_MAX];
        if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
            return -1;
        Logger::Error("Current directory: %s", cCurrentPath);
        return -1;
    }
    
    Logger::Info("Starting D3Serve");
    Service::Init();
    Logger::Info("Creating server on port: %i", SERVER_PORT);
    ServerSocket s;
    s.Listen(SERVER_PORT);
    while (s.isListening())
        HandleClient(s.Accept());
    Logger::Info("Stopping D3Serve");
    s.Close();
    return 0;
}

void HandleClient(ClientSocket c) {
    Logger::Trace("Client connected");
    ClientService client(&c);
    while (c.isConnected()) {
        Packet packetIn = Packet::Read(client);
        if (!packetIn.isValid()) {
            Logger::Error("Invalid packet format: Reading from client");
            break;
        }
        Logger::Trace("PacketIn Info: %s", packetIn.toString().c_str());
        Packet packetOut = Service::CallService(&client, packetIn);
        if (!packetOut.isValid()) {
            Logger::Error("Invalid packet format: Invalid service call");
            break;
        }
        Logger::Trace("PacketOut Info: %s", packetOut.toString().c_str());
        packetOut.Write(client);
    }
    c.Close();
    Logger::Trace("Client disconnected");
}