

import json

def json_pad(obj, size=1024):
    obj['_padding'] = ''
    s = json.dumps(obj)

    if len(s) > size:
        raise Exception("JSON object too large; %d > %d bytes" % (len(s), size))

    obj['_padding'] = 'A'*(size - len(s))
    return json.dumps(obj)




