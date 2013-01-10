#ifndef DECODERTAB_H
#define DECODERTAB_H

#include <QWidget>

class QLabel;

class DecoderTab : public QWidget
{
    Q_OBJECT
public:
    explicit DecoderTab(QWidget *parent = 0);

signals:

public slots:
    void inputByteCount(quint32);
    void candidatePayloadCount(quint32);
    void overLengthMessageCount(quint32);
    void lengthOddCount(quint32);
    void manchesterInvalidCount(quint32);
    void checkSumErrorCount(quint32);
    void validMessageCount(quint32);
    void seventyCount(quint32);
    void collisionCount(quint32);

private:
    QLabel *numInputBytesLabel;
    QLabel *numCandidateMessagesLabel;
    QLabel *numOverLengthMessagesLabel;
    QLabel *numLengthOddPayloadsLabel;
    QLabel *numManchesterInvalidLabel;
    QLabel *numCheckSumErrorsLabel;
    QLabel *numValidMessagesLabel;
    QLabel *numSeventyLabel;
    QLabel *numCollisionLabel;
};

#endif // DECODERTAB_H
