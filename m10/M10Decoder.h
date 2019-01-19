/* 
 * File:   M10Decoder.h
 * Author: Viproz
 * Used code from rs1729
 * Created on December 12, 2018, 11:31 PM
 */

#ifndef M10DECODER_H
#define M10DECODER_H
#define EOF_INT  0x1000000
#define FRAME_LEN       (100+1)   // 0x64+1
#define AUX_LEN         20
#define DATA_LENGTH     (FRAME_LEN + AUX_LEN + 2)

#define stdFLEN        0x64  // pos[0]=0x64
#define pos_Check     (stdFLEN-1)  // 2 byte

#define AVG_NUM 5.

#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include "M10GeneralParser.h"
#include "AudioFile.h"

class M10Decoder {
public:
    M10Decoder();
    virtual ~M10Decoder();
    virtual int startDecode(std::string fname);
    virtual double findFrameStart();
    virtual int decodeMessage(double initialPos);
    
    void setRaw(bool b);
    void setDispResult(bool b) {dispResult = b;}
    void setChannel(int c) {targetedChannel = c;}
    void setTryMethodSign(bool b) {trySign = b;}
    void setTryMethodRepair(bool b) {tryRepair = b;}
    void setTryStats(bool b) {tryStats = b;}
    void setVerboseLevel(int level) {verboseLevel = level;}
    
protected:
    int decodeMethodCompare(double initialPos);
    int decodeMethodSign(double initialPos);
    int getNextBufferValue();
    bool checkCRC();
    int update_checkM10(int c, unsigned short b);
    void bits2bytes();

    M10GeneralParser *m10Parser;
    M10GeneralParser *m10GTop;
    M10GeneralParser *m10Ptu;
    
    AudioFile *audioFile;
    
    bool dispResult = false;
    bool dispRaw = false;
    bool trySign = false;
    bool tryRepair = false;
    bool tryStats = false;
    int verboseLevel = 0;
    int targetedChannel = 0;
    double samplesPerBit = 0;
    double baudRate = 9615;
    static char header[];
    std::string filename;
    
    std::vector<int> *frameSamples;
    int curIndex = 0;
    int samplesBufLength = 0;
    int correctFrames = 0;
    int totalFrames = 0;
    int frameLength = 0;
    
    std::array<unsigned char, DATA_LENGTH> frame_bytes;
    std::array<unsigned char, (DATA_LENGTH)*8> frame_bits;
    std::array<unsigned char, DATA_LENGTH> lastGoodFrame;
};

#endif /* M10DECODER_H */

