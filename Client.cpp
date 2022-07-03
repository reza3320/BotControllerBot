#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void main()
{
	string ipAddress = "127.0.0.1";			// IP Address of the server
	int port = 54000;						// Listening port # on the server

	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	// Do-while loop to send and receive data
	char buf[4096];
	string userInput;
	string userInput2;

	while (true)
	{
		// Prompt the user for some text
		cout << "> ";
		userInput = "click";
		userInput2 = "wait";
		string state;
		ifstream myreadfile("storage.txt");
		myreadfile >> state;
		myreadfile.close();



		if (state == "")
		{
			ofstream myfile("storage.txt");

			cout << "Give me your HotKey to bind!" << endl;
			char hotkey = getch();
			int value1 = hotkey;

			myfile << value1;
			myfile.close();
			continue;
		}

		else
		{
			stringstream statevalue(state);
			int x = 0;
			statevalue >> x;
			
			while (true)
			{
				
				char key = getch();
				int value2 = key;	
				if (value2 == x)
				{


					// Send the text
					
					int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
						
					
					cout << "function";
					
					
					/*
					if (sendResult != SOCKET_ERROR)
					{
						// Wait for response
						ZeroMemory(buf, 4096);
						int bytesReceived = recv(sock, buf, 4096, 0);
						if (bytesReceived > 0)
						{
							// Echo response to console
							cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;

						}

					}
					*/
					//function send to python
					//Sleep(500)
					
				}
				
				
			}

			



		}

	}







	// Gracefully close down everything
	//closesocket(sock);
	//WSACleanup();
}
