# sifas-dat
Change the server host for patched SIFAS apk client.

# Usage
```bash
# disassemble the patched client
java -jar apktool.jar d my-sifas-client.apk

# change the host
sifas-dat my-sifas-client/assets/bin/Data/Managed/Metadata/global-metadata.dat http://192.168.1.123 http://192.168.1.170

# replace global-metadata.dat with output.dat (make sure to rename it)
# reassemble
java -jar apktool.jar b my-sifas-client

# now you have to sign your apk file and voila!
```