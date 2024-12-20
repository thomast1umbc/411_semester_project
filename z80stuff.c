/* Basic implementation of the DAA instruction */
DAAOP:
    {
        int low = cpu->af.b.h & 0x0F;
        int high = cpu->af.b.h >> 4;
        int cf = cpu->af.b.l & 0x01;
        int hf = cpu->af.b.l & 0x10;
        int nf = cpu->af.b.l & 0x02;

        if(cf) {
            _value = (low < 0x0A && !hf) ? 0x60 : 0x66;
        }
        else {
            if(low < 0x0A) {
                if(high < 0x0A) {
                    _value = (hf) ? 0x06 : 0x00;
                }
                else {
                    _value = (hf) ? 0x66 : 0x60;
                }
            }
            else {
                _value = (high < 0x09) ? 0x06 : 0x66;
            }
        }

        if(nf) {
            cpu->af.b.h -= _value;
        }
        else {
            cpu->af.b.h += _value;
        }

        cpu->af.b.l = ZSPXYtable[cpu->af.b.h] | (nf);

        if(_value >= 0x60)
            cpu->af.b.l |= 0x01;

        if(nf) {
            if(hf && low < 0x06) {
                cpu->af.b.l |= 0x10;
            }
        }
        else if(low >= 10) {
            cpu->af.b.l |= 0x10;
        }

        cycles_done += 4;
        goto out;
    }

/* Flag tables */
static const uint8_t ZStable[256] =
{
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80
};

static const uint8_t ZSXYtable[256] =
{
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x88, 0x88, 0x88, 0x88,
    0x88, 0x88, 0x88, 0x88, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
    0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA8, 0xA8,
    0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA0, 0xA0, 0xA0, 0xA0,
    0xA0, 0xA0, 0xA0, 0xA0, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8,
    0xA8, 0xA8, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x88, 0x88, 0x88, 0x88,
    0x88, 0x88, 0x88, 0x88, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0,
    0xA0, 0xA0, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8,
    0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA8, 0xA8,
    0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8
};

static const uint8_t ZSPXYtable[256] =
{
    0x44, 0x00, 0x00, 0x04, 0x00, 0x04, 0x04, 0x00, 0x08, 0x0C,
    0x0C, 0x08, 0x0C, 0x08, 0x08, 0x0C, 0x00, 0x04, 0x04, 0x00,
    0x04, 0x00, 0x00, 0x04, 0x0C, 0x08, 0x08, 0x0C, 0x08, 0x0C,
    0x0C, 0x08, 0x20, 0x24, 0x24, 0x20, 0x24, 0x20, 0x20, 0x24,
    0x2C, 0x28, 0x28, 0x2C, 0x28, 0x2C, 0x2C, 0x28, 0x24, 0x20,
    0x20, 0x24, 0x20, 0x24, 0x24, 0x20, 0x28, 0x2C, 0x2C, 0x28,
    0x2C, 0x28, 0x28, 0x2C, 0x00, 0x04, 0x04, 0x00, 0x04, 0x00,
    0x00, 0x04, 0x0C, 0x08, 0x08, 0x0C, 0x08, 0x0C, 0x0C, 0x08,
    0x04, 0x00, 0x00, 0x04, 0x00, 0x04, 0x04, 0x00, 0x08, 0x0C,
    0x0C, 0x08, 0x0C, 0x08, 0x08, 0x0C, 0x24, 0x20, 0x20, 0x24,
    0x20, 0x24, 0x24, 0x20, 0x28, 0x2C, 0x2C, 0x28, 0x2C, 0x28,
    0x28, 0x2C, 0x20, 0x24, 0x24, 0x20, 0x24, 0x20, 0x20, 0x24,
    0x2C, 0x28, 0x28, 0x2C, 0x28, 0x2C, 0x2C, 0x28, 0x80, 0x84,
    0x84, 0x80, 0x84, 0x80, 0x80, 0x84, 0x8C, 0x88, 0x88, 0x8C,
    0x88, 0x8C, 0x8C, 0x88, 0x84, 0x80, 0x80, 0x84, 0x80, 0x84,
    0x84, 0x80, 0x88, 0x8C, 0x8C, 0x88, 0x8C, 0x88, 0x88, 0x8C,
    0xA4, 0xA0, 0xA0, 0xA4, 0xA0, 0xA4, 0xA4, 0xA0, 0xA8, 0xAC,
    0xAC, 0xA8, 0xAC, 0xA8, 0xA8, 0xAC, 0xA0, 0xA4, 0xA4, 0xA0,
    0xA4, 0xA0, 0xA0, 0xA4, 0xAC, 0xA8, 0xA8, 0xAC, 0xA8, 0xAC,
    0xAC, 0xA8, 0x84, 0x80, 0x80, 0x84, 0x80, 0x84, 0x84, 0x80,
    0x88, 0x8C, 0x8C, 0x88, 0x8C, 0x88, 0x88, 0x8C, 0x80, 0x84,
    0x84, 0x80, 0x84, 0x80, 0x80, 0x84, 0x8C, 0x88, 0x88, 0x8C,
    0x88, 0x8C, 0x8C, 0x88, 0xA0, 0xA4, 0xA4, 0xA0, 0xA4, 0xA0,
    0xA0, 0xA4, 0xAC, 0xA8, 0xA8, 0xAC, 0xA8, 0xAC, 0xAC, 0xA8,
    0xA4, 0xA0, 0xA0, 0xA4, 0xA0, 0xA4, 0xA4, 0xA0, 0xA8, 0xAC,
    0xAC, 0xA8, 0xAC, 0xA8, 0xA8, 0xAC
};
