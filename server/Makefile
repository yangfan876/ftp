object = com_recv.o server.o

server: $(object)
	gcc -g -o $@ $(object)

com_recv.o: com_recv.c
	gcc -g -c -o $@ $<

server.o: server.c
	gcc -g -c -o $@ $<

clean:
	rm -rf $(object)
	rm -rf server
