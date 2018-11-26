THIS IS CHAT APPLICATION WHICH WORK ON AD-HOC NETWORK 
CREATE FIRST AD-HOC NETWORK

FOR TRY PROTOCOL THEN FOLLOW THE FOLLOWING STEP
	gcc reciver.c -o .reciver
	<RUN RECIVER FIRST>
	./.reciver 
	gcc sender.c -o .sender
	 ./.reciver

MORE GENRAL WAY IS TO EVERY MACHINE WILL HAVE BOTH SENDER AND RECIVER AS WELL
BOTH ARE NEEDED FOR TWO WAY COMMUNICATION
FOR THIS FOLLOW THE FOLLOWING STEPS
	gcc messanger.c -o .messanger
	./.messanger

This Will Work If One Host 'A' Is Within Range Of 'B' 
And B is Within Range Of 'C' then A can Send Message To C directly