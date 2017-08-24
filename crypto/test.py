import libPaillierPublicParameters
import libPaillierAdapter as Paillier

# instantiate crypto method
cm = Paillier.PaillierAdapter(128,1)

# encrypt 2 with rec level 1
print(cm.encrypt(2,1))

# get public parameters of crypto method, in order to be able to decrypt
cm.getPublicParameters()

x = cm.encrypt(3, 2)
params = cm.getPublicParameters()
dec = cm.decrypt(x, 2, params.getCiphBitsizeFromRecLvl(2)/8, params.getAbsorptionBitsize(1)/8)

print(dec)

