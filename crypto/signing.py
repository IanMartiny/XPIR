
import ed25519  # Install from https://github.com/warner/python-ed25519


# Generate a keypair
priv, pub = ed25519.create_keypair()

# Write private/public key to disk
open('privkey', 'wb').write(priv.to_seed())
open('pubkey', 'wb').write(pub.to_bytes())


# ---- Can just start here if using a persistant private key
# Load private key from disk
priv_seed = open('privkey', 'rb').read()
priv = ed25519.SigningKey(priv_seed)
pub = priv.get_verifying_key()   # re-generate public key


# Client would load pubkey from disk:
pub = ed25519.VerifyingKey(open('pubkey', 'rb').read())
print 'Loaded privkey: %s' % (priv.to_seed().encode('hex'))
print 'Loaded pubkey:  %s' % (pub.to_bytes().encode('hex'))



# Server signs some data (deterministic)
msg = 'Hello, world'
sig = priv.sign(msg)
print 'Made signature: %s' % (sig.encode('hex'))



# Verify signature
try:
    pub.verify(sig, msg)
    print '[+] Signature matched!'
except ed25519.BadSignatureError:
    print '[-] Error: bad signature!!'



# Test with a bad signature
try:
    pub.verify(sig, msg + '\x00')
    print '[-] Signature matched (But should not have!)'
except ed25519.BadSignatureError:
    print '[+] Signature fails verify with changed data'
