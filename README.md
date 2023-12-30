# sifas-dat
Change the host or any other metadata string for SIFAS apk client.

# Usage
A common use case is to change/overwrite the server host.

```bash
# disassemble the patched client
java -jar apktool.jar d my-sifas-client.apk

# change the host
sifas-dat my-sifas-client/assets/bin/Data/Managed/Metadata/global-metadata.dat 192.168.1.123 192.168.1.170

# replace global-metadata.dat with output.dat (make sure to rename it)
# reassemble
java -jar apktool.jar b my-sifas-client

# now you have to sign your apk file and voila!
```