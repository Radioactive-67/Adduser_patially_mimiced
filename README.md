#adduser
This c program mimics the adduser function of linux terminal partially.
It stores the data in passwd and shadow file which are stored in a folder named "etc" which is created if not already present in the present working directory.
The code checks for unique username and uID and forces 7arguments in the form:
adduser -u <uID> -g <gID> -c "<comments"> <username>
    eg.
   adduser -u 12 -g 1 -c "user1" Ashish 
