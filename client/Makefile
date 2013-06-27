object = com_send.o login.o ftp_shell.o client.o

ftp: $(object)
	gcc -o $@ $(object)

ftp_shell.o: ftp_shell.c
	gcc -g -c -o $@ $<

client.o: client.c
	gcc -g -c -o $@ $<

login.o: login.c
	gcc -g -c -o $@ $<

com_send.o: com_send.c
	gcc -g -c -o $@ $<

clean:
	rm -rf $(object)
	rm -rf ftp
