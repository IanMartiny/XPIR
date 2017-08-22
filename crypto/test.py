import libPaillierAdapter as Paillier

# instantiate crypto method
cm = Paillier.PaillierAdapter(128,1)

# encrypt 2 with rec level 1
print(cm.encrypt(2,1).encode("base64"))

# get public parameters of crypto method, in order to be able to decrypt
cm.getPublicParameters()
