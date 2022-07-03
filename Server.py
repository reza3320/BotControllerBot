import discord
import socket
import sys

TOKEN = 'xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx'

client = discord.Client()

# Create a stream based socket(i.e, a TCP socket)
# operating on IPv4 addressing scheme
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)



# Bind and listen
serverSocket.bind(("127.0.0.1",54000))
serverSocket.listen(5)
print ('hello admin')


@client.event
async def on_ready():
	print('We have loggerd in as {0.user}'.format(client))


# Accept connections



@client.event
async def on_message(message):
	
	username = str(message.author).split('#')[0]
	user_message = str(message.content)
	channel = str(message.channel.name)
	print(f'{username}: {user_message} ({channel})')	

	if message.author == client.user:
		return

	if user_message.lower() == '!controller':
		await message.channel.send(f'Sup {username}??')
		return
	if user_message.lower() == '!ct':
		await message.channel.send(f'OnDuty Sir!')
		(clientConnected, clientAddress) = serverSocket.accept()
		print("Accepted a connection request from %s:%s"%(clientAddress[0], clientAddress[1]))
		while(True):
			dataFromClient = clientConnected.recv(1024)
			dataFromClient2 = dataFromClient.decode()
			print(dataFromClient.decode())
			
			await message.channel.send(f'!pause')
			continue
		return
	if user_message.lower() == 'hello':
		await message.channel.send(f'Hello {username}!')
		return
	elif user_message.lower() == 'bye':
		await message.channel.send(f'See you later {username}!')
		return
client.run(TOKEN)

#if message.channel.name == client.channel
			




