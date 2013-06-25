object = login.o client.o

client.o: client.c
	gcc -g -c -o $@ $<

login.o: login.c
	gcc -g -c -o $@ $<

ftp: $(object)
	gcc -o $@ $(object)

clean:
	rm -rf $(object)
	rm ftp
