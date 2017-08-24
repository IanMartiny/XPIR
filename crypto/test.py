import libPaillierPublicParameters
import libPaillierPublicKey
import libPaillierAdapter as Paillier

# instantiate crypto method
cm = Paillier.PaillierAdapter(128,1)

# encrypt 2 with rec level 1
s = cm.encrypt(2,2)

# get public parameters of crypto method, in order to be able to decrypt
cm.getPublicParameters()

ct = cm.encrypt(3,2)
ct2 = cm.encrypt(5,2)
params = cm.getPublicParameters()
pt = cm.decrypt(ct, 2, params.getCiphBitsizeFromRecLvl(2)/8, params.getAbsorptionBitsize(1)/8)

print(pt)

cta = cm.e_add_wrap(ct, ct2, 2)
pt = cm.decrypt(cta, 2, params.getCiphBitsizeFromRecLvl(2)/8, params.getAbsorptionBitsize(1)/8)

print(pt)
