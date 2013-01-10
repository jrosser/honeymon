#include "decodertab.h"

#include <QtGui>

DecoderTab::DecoderTab(QWidget *parent) :
    QWidget(parent)
{
    //group box for decoder statistics
    QGroupBox *decoderStatsGroup = new QGroupBox("Decoder Statistics");

    //labels
    QLabel *inputBytesLabel         = new QLabel("Number of input bytes");
    QLabel *candidateMessagesLabel  = new QLabel("Number of candidate payloads");
    QLabel *overLengthMessagesLabel = new QLabel("Number of overlength messages");
    QLabel *lengthOddPayloadsLabel  = new QLabel("Number of odd length messages");
    QLabel *manchesterInvalidLabel  = new QLabel("Number of Manchester errors");
    QLabel *checkSumErrorsLabel     = new QLabel("Number of checksum errors");
    QLabel *validMessagesLabel      = new QLabel("Number of valid messages");
    QLabel *seventyLabel            = new QLabel("Number of messages containing 0x70");
    QLabel *collisionsLabel         = new QLabel("Number of message collisions");

    //grid layout for stats labels and values
    QGridLayout *decoderStatsLayout = new QGridLayout();
    decoderStatsLayout->addWidget(inputBytesLabel, 0, 0);
    decoderStatsLayout->addWidget(candidateMessagesLabel, 1, 0);
    decoderStatsLayout->addWidget(overLengthMessagesLabel, 2, 0);
    decoderStatsLayout->addWidget(lengthOddPayloadsLabel, 3, 0);
    decoderStatsLayout->addWidget(manchesterInvalidLabel, 4, 0);
    decoderStatsLayout->addWidget(checkSumErrorsLabel, 5, 0);
    decoderStatsLayout->addWidget(validMessagesLabel, 6, 0);
    decoderStatsLayout->addWidget(seventyLabel, 7, 0);
    decoderStatsLayout->addWidget(collisionsLabel, 8, 0);

    //values
    numInputBytesLabel = new QLabel("0");
    numCandidateMessagesLabel = new QLabel("0");
    numOverLengthMessagesLabel = new QLabel("0");
    numLengthOddPayloadsLabel = new QLabel("0");
    numManchesterInvalidLabel = new QLabel("0");
    numCheckSumErrorsLabel = new QLabel("0");
    numValidMessagesLabel = new QLabel("0");
    numSeventyLabel = new QLabel("0");
    numCollisionLabel = new QLabel("0");

    decoderStatsLayout->addWidget(numInputBytesLabel, 0, 1);
    decoderStatsLayout->addWidget(numCandidateMessagesLabel, 1, 1);
    decoderStatsLayout->addWidget(numOverLengthMessagesLabel, 2, 1);
    decoderStatsLayout->addWidget(numLengthOddPayloadsLabel, 3, 1);
    decoderStatsLayout->addWidget(numManchesterInvalidLabel, 4, 1);
    decoderStatsLayout->addWidget(numCheckSumErrorsLabel, 5, 1);
    decoderStatsLayout->addWidget(numValidMessagesLabel, 6, 1);
    decoderStatsLayout->addWidget(numSeventyLabel, 7, 1);
    decoderStatsLayout->addWidget(numCollisionLabel, 8, 1);

    decoderStatsGroup->setLayout(decoderStatsLayout);

    //vertical layout down the tab
    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(decoderStatsGroup);
    vlayout->addStretch();

    //set the layout for the whole tab
    this->setLayout(vlayout);
}

void DecoderTab::inputByteCount(quint32 n)
{
    numInputBytesLabel->setNum((int)n);
}

void DecoderTab::candidatePayloadCount(quint32 n)
{
    numCandidateMessagesLabel->setNum((int)n);
}

void DecoderTab::overLengthMessageCount(quint32 n)
{
    numOverLengthMessagesLabel->setNum((int)n);
}

void DecoderTab::lengthOddCount(quint32 n)
{
    numLengthOddPayloadsLabel->setNum((int)n);
}

void DecoderTab::manchesterInvalidCount(quint32 n)
{
    numManchesterInvalidLabel->setNum((int)n);
}

void DecoderTab::checkSumErrorCount(quint32 n)
{
    numCheckSumErrorsLabel->setNum((int)n);
}

void DecoderTab::validMessageCount(quint32 n)
{
    numValidMessagesLabel->setNum((int)n);
}

void DecoderTab::seventyCount(quint32 n)
{
    numSeventyLabel->setNum((int)n);
}

void DecoderTab::collisionCount(quint32 n)
{
    numCollisionLabel->setNum((int)n);
}
