#include "nodenames.h"

NodeNames::NodeNames()
{
    nameMap.insert(0x11c9c1, "Loft");
    nameMap.insert(0x11c9c2, "Kitchen");
    nameMap.insert(0x11c9cb, "Lounge");
    nameMap.insert(0x11c9cd, "Hall");
    nameMap.insert(0x11c9d0, "Cons. Tall");
    nameMap.insert(0x11c9d6, "Conservatory");
    nameMap.insert(0x126a8a, "Piano Rm");
    nameMap.insert(0x126a8b, "Front Bed");
    nameMap.insert(0x126a95, "Back Bed");
    nameMap.insert(0x333d48, "Prog2");
    nameMap.insert(0x334ab3, "Prog1");
}

QString NodeNames::idToName(quint32 id)
{
    if(nameMap.contains(id)) {
        return nameMap[id];
    } else {
        return QString("%1") .arg(id, 6, 16, QChar('0'));
    }
}
