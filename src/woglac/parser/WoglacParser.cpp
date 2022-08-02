
// Generated from Woglac.g4 by ANTLR 4.10.1


#include "WoglacListener.h"

#include "WoglacParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct WoglacParserStaticData final {
  WoglacParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  WoglacParserStaticData(const WoglacParserStaticData&) = delete;
  WoglacParserStaticData(WoglacParserStaticData&&) = delete;
  WoglacParserStaticData& operator=(const WoglacParserStaticData&) = delete;
  WoglacParserStaticData& operator=(WoglacParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag woglacParserOnceFlag;
WoglacParserStaticData *woglacParserStaticData = nullptr;

void woglacParserInitialize() {
  assert(woglacParserStaticData == nullptr);
  auto staticData = std::make_unique<WoglacParserStaticData>(
    std::vector<std::string>{
      "module", "statement", "scope", "contentOrSemicolon", "pragmaStatement", 
      "variableDefinition", "paramDefinition", "biomeParamDefinition", "paramSetStatement", 
      "biomeConditionStatement", "structureConditionStatement", "ruleExpansionStatement", 
      "componentNodeStatement", "componentNodeStatementCommonPart", "componentNodePropertiesSection", 
      "componentNodeOrientationExpression", "componentAreaStatement", "componentBlockStatement", 
      "componentIncludeStatement", "componentIncludeStatementParam", "componentIncludeStatementBlockParam", 
      "componentIncludeStatementNodeParam", "positionExpression", "expression", 
      "parentExpression", "ternaryExpression", "logicalExpression", "andExpression", 
      "orExpression", "comparisonExpression", "addExpression", "multExpression", 
      "unaryExpression", "inlineFunctionCallExpression", "atomicExpression", 
      "arugmentListExpression", "biomeParamExpression", "functionCallExpression", 
      "extendedIdentifier", "literalExpression"
    },
    std::vector<std::string>{
      "", "'extend'", "'namespace'", "'rule'", "'component'", "'biome'", 
      "'{'", "'}'", "';'", "'pragma'", "'='", "'export'", "'param'", "'\\u003F='", 
      "'condition'", "'+-'", "'->'", "'::'", "'void'", "'!'", "':'", "'node'", 
      "'('", "'|'", "'-'", "')'", "'+'", "'area'", "'#'", "'\\u003F'", "'block'", 
      "'include'", "','", "'&&'", "'||'", "'.'", "'~'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "LineComment", "BlockComment", "Whitespace", "Type", "BlockLiteral", 
      "ComparisonOp", "BoolLiteral", "StringLiteral", "MultOp", "Identifier", 
      "NumericLiteral"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,47,496,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,1,0,5,0,82,8,0,10,0,12,0,85,
  	9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,102,
  	8,1,1,2,3,2,105,8,2,1,2,1,2,1,2,1,2,1,2,1,2,5,2,113,8,2,10,2,12,2,116,
  	9,2,1,2,3,2,119,8,2,1,3,1,3,5,3,123,8,3,10,3,12,3,126,9,3,1,3,1,3,3,3,
  	130,8,3,1,4,1,4,1,4,1,4,1,4,3,4,137,8,4,3,4,139,8,4,1,4,1,4,1,5,3,5,144,
  	8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,3,6,154,8,6,3,6,156,8,6,1,6,1,6,1,
  	6,1,6,1,6,3,6,163,8,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,
  	3,8,177,8,8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,3,9,187,8,9,3,9,189,8,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,3,10,201,8,10,3,10,203,8,10,1,
  	10,1,10,1,10,1,10,1,11,1,11,3,11,211,8,11,1,11,1,11,1,11,1,11,3,11,217,
  	8,11,1,11,3,11,220,8,11,1,11,1,11,3,11,224,8,11,1,11,1,11,3,11,228,8,
  	11,1,11,1,11,1,12,1,12,3,12,234,8,12,1,12,1,12,1,12,1,12,1,13,3,13,241,
  	8,13,1,13,3,13,244,8,13,1,13,1,13,3,13,248,8,13,1,13,1,13,1,14,1,14,3,
  	14,254,8,14,1,14,3,14,257,8,14,1,14,3,14,260,8,14,1,14,1,14,3,14,264,
  	8,14,1,14,1,14,1,15,1,15,1,15,1,16,1,16,3,16,273,8,16,1,16,1,16,1,16,
  	1,16,1,16,3,16,280,8,16,1,16,3,16,283,8,16,1,16,3,16,286,8,16,1,16,3,
  	16,289,8,16,1,16,3,16,292,8,16,1,16,1,16,1,17,1,17,3,17,298,8,17,1,17,
  	1,17,1,17,3,17,303,8,17,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,
  	5,18,314,8,18,10,18,12,18,317,9,18,1,18,1,18,1,19,1,19,3,19,323,8,19,
  	1,20,1,20,1,20,1,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,
  	1,22,1,22,1,22,1,22,1,22,3,22,344,8,22,1,22,1,22,1,23,1,23,1,24,1,24,
  	1,24,1,24,1,25,1,25,1,25,1,25,3,25,358,8,25,1,25,1,25,1,25,3,25,363,8,
  	25,1,26,1,26,3,26,367,8,26,1,27,1,27,1,27,1,27,1,27,1,27,5,27,375,8,27,
  	10,27,12,27,378,9,27,1,28,1,28,1,28,1,28,1,28,1,28,5,28,386,8,28,10,28,
  	12,28,389,9,28,1,29,1,29,1,29,1,29,1,29,3,29,396,8,29,1,30,1,30,1,30,
  	1,30,1,30,1,30,5,30,404,8,30,10,30,12,30,407,9,30,1,31,1,31,1,31,1,31,
  	1,31,1,31,5,31,415,8,31,10,31,12,31,418,9,31,1,32,1,32,1,32,1,32,1,32,
  	3,32,425,8,32,1,33,1,33,1,33,1,33,1,33,1,33,1,33,5,33,434,8,33,10,33,
  	12,33,437,9,33,1,34,1,34,1,34,1,34,1,34,3,34,444,8,34,1,35,1,35,1,35,
  	1,35,5,35,450,8,35,10,35,12,35,453,9,35,1,35,3,35,456,8,35,3,35,458,8,
  	35,1,35,1,35,1,36,1,36,1,36,1,36,1,36,1,36,1,36,5,36,469,8,36,10,36,12,
  	36,472,9,36,1,36,1,36,1,37,1,37,1,37,1,38,1,38,1,38,5,38,482,8,38,10,
  	38,12,38,485,9,38,1,39,3,39,488,8,39,1,39,1,39,1,39,1,39,3,39,494,8,39,
  	1,39,0,5,54,56,60,62,66,40,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,
  	32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,
  	78,0,5,1,0,2,5,1,0,3,4,1,0,3,5,2,0,24,24,26,26,2,0,28,28,36,36,532,0,
  	83,1,0,0,0,2,101,1,0,0,0,4,118,1,0,0,0,6,129,1,0,0,0,8,131,1,0,0,0,10,
  	143,1,0,0,0,12,155,1,0,0,0,14,166,1,0,0,0,16,176,1,0,0,0,18,188,1,0,0,
  	0,20,202,1,0,0,0,22,208,1,0,0,0,24,233,1,0,0,0,26,240,1,0,0,0,28,251,
  	1,0,0,0,30,267,1,0,0,0,32,272,1,0,0,0,34,297,1,0,0,0,36,308,1,0,0,0,38,
  	322,1,0,0,0,40,324,1,0,0,0,42,330,1,0,0,0,44,335,1,0,0,0,46,347,1,0,0,
  	0,48,349,1,0,0,0,50,362,1,0,0,0,52,366,1,0,0,0,54,368,1,0,0,0,56,379,
  	1,0,0,0,58,395,1,0,0,0,60,397,1,0,0,0,62,408,1,0,0,0,64,424,1,0,0,0,66,
  	426,1,0,0,0,68,443,1,0,0,0,70,445,1,0,0,0,72,461,1,0,0,0,74,475,1,0,0,
  	0,76,478,1,0,0,0,78,493,1,0,0,0,80,82,3,2,1,0,81,80,1,0,0,0,82,85,1,0,
  	0,0,83,81,1,0,0,0,83,84,1,0,0,0,84,86,1,0,0,0,85,83,1,0,0,0,86,87,5,0,
  	0,1,87,1,1,0,0,0,88,102,3,8,4,0,89,102,3,12,6,0,90,102,3,14,7,0,91,102,
  	3,16,8,0,92,102,3,18,9,0,93,102,3,10,5,0,94,102,3,22,11,0,95,102,3,4,
  	2,0,96,102,3,24,12,0,97,102,3,34,17,0,98,102,3,32,16,0,99,102,3,20,10,
  	0,100,102,3,36,18,0,101,88,1,0,0,0,101,89,1,0,0,0,101,90,1,0,0,0,101,
  	91,1,0,0,0,101,92,1,0,0,0,101,93,1,0,0,0,101,94,1,0,0,0,101,95,1,0,0,
  	0,101,96,1,0,0,0,101,97,1,0,0,0,101,98,1,0,0,0,101,99,1,0,0,0,101,100,
  	1,0,0,0,102,3,1,0,0,0,103,105,5,1,0,0,104,103,1,0,0,0,104,105,1,0,0,0,
  	105,106,1,0,0,0,106,107,7,0,0,0,107,108,3,76,38,0,108,109,3,6,3,0,109,
  	119,1,0,0,0,110,114,5,6,0,0,111,113,3,2,1,0,112,111,1,0,0,0,113,116,1,
  	0,0,0,114,112,1,0,0,0,114,115,1,0,0,0,115,117,1,0,0,0,116,114,1,0,0,0,
  	117,119,5,7,0,0,118,104,1,0,0,0,118,110,1,0,0,0,119,5,1,0,0,0,120,124,
  	5,6,0,0,121,123,3,2,1,0,122,121,1,0,0,0,123,126,1,0,0,0,124,122,1,0,0,
  	0,124,125,1,0,0,0,125,127,1,0,0,0,126,124,1,0,0,0,127,130,5,7,0,0,128,
  	130,5,8,0,0,129,120,1,0,0,0,129,128,1,0,0,0,130,7,1,0,0,0,131,132,5,9,
  	0,0,132,138,3,76,38,0,133,136,5,10,0,0,134,137,3,78,39,0,135,137,5,46,
  	0,0,136,134,1,0,0,0,136,135,1,0,0,0,137,139,1,0,0,0,138,133,1,0,0,0,138,
  	139,1,0,0,0,139,140,1,0,0,0,140,141,5,8,0,0,141,9,1,0,0,0,142,144,5,11,
  	0,0,143,142,1,0,0,0,143,144,1,0,0,0,144,145,1,0,0,0,145,146,5,40,0,0,
  	146,147,3,76,38,0,147,148,5,10,0,0,148,149,3,46,23,0,149,150,5,8,0,0,
  	150,11,1,0,0,0,151,153,7,1,0,0,152,154,3,76,38,0,153,152,1,0,0,0,153,
  	154,1,0,0,0,154,156,1,0,0,0,155,151,1,0,0,0,155,156,1,0,0,0,156,157,1,
  	0,0,0,157,158,5,12,0,0,158,159,5,40,0,0,159,162,5,46,0,0,160,161,5,13,
  	0,0,161,163,3,46,23,0,162,160,1,0,0,0,162,163,1,0,0,0,163,164,1,0,0,0,
  	164,165,5,8,0,0,165,13,1,0,0,0,166,167,5,5,0,0,167,168,5,12,0,0,168,169,
  	5,40,0,0,169,170,3,76,38,0,170,171,5,13,0,0,171,172,3,46,23,0,172,173,
  	5,8,0,0,173,15,1,0,0,0,174,175,7,2,0,0,175,177,3,76,38,0,176,174,1,0,
  	0,0,176,177,1,0,0,0,177,178,1,0,0,0,178,179,5,12,0,0,179,180,3,76,38,
  	0,180,181,5,10,0,0,181,182,3,46,23,0,182,183,5,8,0,0,183,17,1,0,0,0,184,
  	186,5,5,0,0,185,187,3,76,38,0,186,185,1,0,0,0,186,187,1,0,0,0,187,189,
  	1,0,0,0,188,184,1,0,0,0,188,189,1,0,0,0,189,190,1,0,0,0,190,191,5,14,
  	0,0,191,192,3,76,38,0,192,193,5,10,0,0,193,194,5,47,0,0,194,195,5,15,
  	0,0,195,196,5,47,0,0,196,197,5,8,0,0,197,19,1,0,0,0,198,200,7,1,0,0,199,
  	201,3,76,38,0,200,199,1,0,0,0,200,201,1,0,0,0,201,203,1,0,0,0,202,198,
  	1,0,0,0,202,203,1,0,0,0,203,204,1,0,0,0,204,205,5,14,0,0,205,206,3,46,
  	23,0,206,207,5,8,0,0,207,21,1,0,0,0,208,210,5,3,0,0,209,211,3,76,38,0,
  	210,209,1,0,0,0,210,211,1,0,0,0,211,212,1,0,0,0,212,219,5,16,0,0,213,
  	216,3,76,38,0,214,215,5,17,0,0,215,217,5,46,0,0,216,214,1,0,0,0,216,217,
  	1,0,0,0,217,220,1,0,0,0,218,220,5,18,0,0,219,213,1,0,0,0,219,218,1,0,
  	0,0,220,223,1,0,0,0,221,222,5,19,0,0,222,224,5,47,0,0,223,221,1,0,0,0,
  	223,224,1,0,0,0,224,227,1,0,0,0,225,226,5,20,0,0,226,228,5,47,0,0,227,
  	225,1,0,0,0,227,228,1,0,0,0,228,229,1,0,0,0,229,230,3,6,3,0,230,23,1,
  	0,0,0,231,232,5,4,0,0,232,234,3,76,38,0,233,231,1,0,0,0,233,234,1,0,0,
  	0,234,235,1,0,0,0,235,236,5,21,0,0,236,237,3,44,22,0,237,238,3,26,13,
  	0,238,25,1,0,0,0,239,241,3,28,14,0,240,239,1,0,0,0,240,241,1,0,0,0,241,
  	243,1,0,0,0,242,244,5,46,0,0,243,242,1,0,0,0,243,244,1,0,0,0,244,247,
  	1,0,0,0,245,246,5,16,0,0,246,248,3,76,38,0,247,245,1,0,0,0,247,248,1,
  	0,0,0,248,249,1,0,0,0,249,250,3,6,3,0,250,27,1,0,0,0,251,253,5,22,0,0,
  	252,254,5,10,0,0,253,252,1,0,0,0,253,254,1,0,0,0,254,256,1,0,0,0,255,
  	257,5,23,0,0,256,255,1,0,0,0,256,257,1,0,0,0,257,259,1,0,0,0,258,260,
  	5,24,0,0,259,258,1,0,0,0,259,260,1,0,0,0,260,261,1,0,0,0,261,263,3,30,
  	15,0,262,264,3,30,15,0,263,262,1,0,0,0,263,264,1,0,0,0,264,265,1,0,0,
  	0,265,266,5,25,0,0,266,29,1,0,0,0,267,268,5,46,0,0,268,269,7,3,0,0,269,
  	31,1,0,0,0,270,271,5,4,0,0,271,273,3,76,38,0,272,270,1,0,0,0,272,273,
  	1,0,0,0,273,274,1,0,0,0,274,275,5,27,0,0,275,276,3,44,22,0,276,288,3,
  	44,22,0,277,279,5,22,0,0,278,280,5,28,0,0,279,278,1,0,0,0,279,280,1,0,
  	0,0,280,282,1,0,0,0,281,283,5,19,0,0,282,281,1,0,0,0,282,283,1,0,0,0,
  	283,285,1,0,0,0,284,286,5,29,0,0,285,284,1,0,0,0,285,286,1,0,0,0,286,
  	287,1,0,0,0,287,289,5,25,0,0,288,277,1,0,0,0,288,289,1,0,0,0,289,291,
  	1,0,0,0,290,292,5,46,0,0,291,290,1,0,0,0,291,292,1,0,0,0,292,293,1,0,
  	0,0,293,294,5,8,0,0,294,33,1,0,0,0,295,296,5,4,0,0,296,298,3,76,38,0,
  	297,295,1,0,0,0,297,298,1,0,0,0,298,299,1,0,0,0,299,300,5,30,0,0,300,
  	302,3,44,22,0,301,303,3,44,22,0,302,301,1,0,0,0,302,303,1,0,0,0,303,304,
  	1,0,0,0,304,305,5,10,0,0,305,306,3,46,23,0,306,307,5,8,0,0,307,35,1,0,
  	0,0,308,309,5,4,0,0,309,310,5,31,0,0,310,311,5,44,0,0,311,315,5,6,0,0,
  	312,314,3,38,19,0,313,312,1,0,0,0,314,317,1,0,0,0,315,313,1,0,0,0,315,
  	316,1,0,0,0,316,318,1,0,0,0,317,315,1,0,0,0,318,319,5,7,0,0,319,37,1,
  	0,0,0,320,323,3,40,20,0,321,323,3,42,21,0,322,320,1,0,0,0,322,321,1,0,
  	0,0,323,39,1,0,0,0,324,325,5,47,0,0,325,326,5,16,0,0,326,327,5,30,0,0,
  	327,328,3,46,23,0,328,329,5,8,0,0,329,41,1,0,0,0,330,331,5,47,0,0,331,
  	332,5,16,0,0,332,333,5,21,0,0,333,334,3,26,13,0,334,43,1,0,0,0,335,343,
  	5,22,0,0,336,337,3,46,23,0,337,338,5,32,0,0,338,339,3,46,23,0,339,340,
  	5,32,0,0,340,341,3,46,23,0,341,344,1,0,0,0,342,344,3,46,23,0,343,336,
  	1,0,0,0,343,342,1,0,0,0,344,345,1,0,0,0,345,346,5,25,0,0,346,45,1,0,0,
  	0,347,348,3,50,25,0,348,47,1,0,0,0,349,350,5,22,0,0,350,351,3,46,23,0,
  	351,352,5,25,0,0,352,49,1,0,0,0,353,363,3,52,26,0,354,355,3,52,26,0,355,
  	357,5,29,0,0,356,358,3,52,26,0,357,356,1,0,0,0,357,358,1,0,0,0,358,359,
  	1,0,0,0,359,360,5,20,0,0,360,361,3,50,25,0,361,363,1,0,0,0,362,353,1,
  	0,0,0,362,354,1,0,0,0,363,51,1,0,0,0,364,367,3,54,27,0,365,367,3,56,28,
  	0,366,364,1,0,0,0,366,365,1,0,0,0,367,53,1,0,0,0,368,369,6,27,-1,0,369,
  	370,3,58,29,0,370,376,1,0,0,0,371,372,10,1,0,0,372,373,5,33,0,0,373,375,
  	3,58,29,0,374,371,1,0,0,0,375,378,1,0,0,0,376,374,1,0,0,0,376,377,1,0,
  	0,0,377,55,1,0,0,0,378,376,1,0,0,0,379,380,6,28,-1,0,380,381,3,58,29,
  	0,381,387,1,0,0,0,382,383,10,1,0,0,383,384,5,34,0,0,384,386,3,58,29,0,
  	385,382,1,0,0,0,386,389,1,0,0,0,387,385,1,0,0,0,387,388,1,0,0,0,388,57,
  	1,0,0,0,389,387,1,0,0,0,390,396,3,60,30,0,391,392,3,60,30,0,392,393,5,
  	42,0,0,393,394,3,60,30,0,394,396,1,0,0,0,395,390,1,0,0,0,395,391,1,0,
  	0,0,396,59,1,0,0,0,397,398,6,30,-1,0,398,399,3,62,31,0,399,405,1,0,0,
  	0,400,401,10,1,0,0,401,402,7,3,0,0,402,404,3,62,31,0,403,400,1,0,0,0,
  	404,407,1,0,0,0,405,403,1,0,0,0,405,406,1,0,0,0,406,61,1,0,0,0,407,405,
  	1,0,0,0,408,409,6,31,-1,0,409,410,3,64,32,0,410,416,1,0,0,0,411,412,10,
  	1,0,0,412,413,5,45,0,0,413,415,3,64,32,0,414,411,1,0,0,0,415,418,1,0,
  	0,0,416,414,1,0,0,0,416,417,1,0,0,0,417,63,1,0,0,0,418,416,1,0,0,0,419,
  	425,3,66,33,0,420,421,7,3,0,0,421,425,3,66,33,0,422,423,5,19,0,0,423,
  	425,3,66,33,0,424,419,1,0,0,0,424,420,1,0,0,0,424,422,1,0,0,0,425,65,
  	1,0,0,0,426,427,6,33,-1,0,427,428,3,68,34,0,428,435,1,0,0,0,429,430,10,
  	1,0,0,430,431,5,17,0,0,431,432,5,46,0,0,432,434,3,70,35,0,433,429,1,0,
  	0,0,434,437,1,0,0,0,435,433,1,0,0,0,435,436,1,0,0,0,436,67,1,0,0,0,437,
  	435,1,0,0,0,438,444,3,74,37,0,439,444,3,78,39,0,440,444,3,48,24,0,441,
  	444,3,72,36,0,442,444,3,76,38,0,443,438,1,0,0,0,443,439,1,0,0,0,443,440,
  	1,0,0,0,443,441,1,0,0,0,443,442,1,0,0,0,444,69,1,0,0,0,445,457,5,22,0,
  	0,446,451,3,46,23,0,447,448,5,32,0,0,448,450,3,46,23,0,449,447,1,0,0,
  	0,450,453,1,0,0,0,451,449,1,0,0,0,451,452,1,0,0,0,452,455,1,0,0,0,453,
  	451,1,0,0,0,454,456,5,32,0,0,455,454,1,0,0,0,455,456,1,0,0,0,456,458,
  	1,0,0,0,457,446,1,0,0,0,457,458,1,0,0,0,458,459,1,0,0,0,459,460,5,25,
  	0,0,460,71,1,0,0,0,461,462,5,5,0,0,462,463,5,22,0,0,463,464,3,76,38,0,
  	464,465,5,32,0,0,465,470,5,46,0,0,466,467,5,32,0,0,467,469,3,46,23,0,
  	468,466,1,0,0,0,469,472,1,0,0,0,470,468,1,0,0,0,470,471,1,0,0,0,471,473,
  	1,0,0,0,472,470,1,0,0,0,473,474,5,25,0,0,474,73,1,0,0,0,475,476,5,46,
  	0,0,476,477,3,70,35,0,477,75,1,0,0,0,478,483,5,46,0,0,479,480,5,35,0,
  	0,480,482,5,46,0,0,481,479,1,0,0,0,482,485,1,0,0,0,483,481,1,0,0,0,483,
  	484,1,0,0,0,484,77,1,0,0,0,485,483,1,0,0,0,486,488,7,4,0,0,487,486,1,
  	0,0,0,487,488,1,0,0,0,488,489,1,0,0,0,489,494,5,47,0,0,490,494,5,41,0,
  	0,491,494,5,43,0,0,492,494,5,44,0,0,493,487,1,0,0,0,493,490,1,0,0,0,493,
  	491,1,0,0,0,493,492,1,0,0,0,494,79,1,0,0,0,60,83,101,104,114,118,124,
  	129,136,138,143,153,155,162,176,186,188,200,202,210,216,219,223,227,233,
  	240,243,247,253,256,259,263,272,279,282,285,288,291,297,302,315,322,343,
  	357,362,366,376,387,395,405,416,424,435,443,451,455,457,470,483,487,493
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  woglacParserStaticData = staticData.release();
}

}

WoglacParser::WoglacParser(TokenStream *input) : WoglacParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

WoglacParser::WoglacParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  WoglacParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *woglacParserStaticData->atn, woglacParserStaticData->decisionToDFA, woglacParserStaticData->sharedContextCache, options);
}

WoglacParser::~WoglacParser() {
  delete _interpreter;
}

const atn::ATN& WoglacParser::getATN() const {
  return *woglacParserStaticData->atn;
}

std::string WoglacParser::getGrammarFileName() const {
  return "Woglac.g4";
}

const std::vector<std::string>& WoglacParser::getRuleNames() const {
  return woglacParserStaticData->ruleNames;
}

const dfa::Vocabulary& WoglacParser::getVocabulary() const {
  return woglacParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView WoglacParser::getSerializedATN() const {
  return woglacParserStaticData->serializedATN;
}


//----------------- ModuleContext ------------------------------------------------------------------

WoglacParser::ModuleContext::ModuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::ModuleContext::EOF() {
  return getToken(WoglacParser::EOF, 0);
}

std::vector<WoglacParser::StatementContext *> WoglacParser::ModuleContext::statement() {
  return getRuleContexts<WoglacParser::StatementContext>();
}

WoglacParser::StatementContext* WoglacParser::ModuleContext::statement(size_t i) {
  return getRuleContext<WoglacParser::StatementContext>(i);
}


size_t WoglacParser::ModuleContext::getRuleIndex() const {
  return WoglacParser::RuleModule;
}

void WoglacParser::ModuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterModule(this);
}

void WoglacParser::ModuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitModule(this);
}

WoglacParser::ModuleContext* WoglacParser::module() {
  ModuleContext *_localctx = _tracker.createInstance<ModuleContext>(_ctx, getState());
  enterRule(_localctx, 0, WoglacParser::RuleModule);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(83);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WoglacParser::T__0)
      | (1ULL << WoglacParser::T__1)
      | (1ULL << WoglacParser::T__2)
      | (1ULL << WoglacParser::T__3)
      | (1ULL << WoglacParser::T__4)
      | (1ULL << WoglacParser::T__5)
      | (1ULL << WoglacParser::T__8)
      | (1ULL << WoglacParser::T__10)
      | (1ULL << WoglacParser::T__11)
      | (1ULL << WoglacParser::T__13)
      | (1ULL << WoglacParser::T__20)
      | (1ULL << WoglacParser::T__26)
      | (1ULL << WoglacParser::T__29)
      | (1ULL << WoglacParser::Type))) != 0)) {
      setState(80);
      antlrcpp::downCast<ModuleContext *>(_localctx)->statementContext = statement();
      antlrcpp::downCast<ModuleContext *>(_localctx)->content.push_back(antlrcpp::downCast<ModuleContext *>(_localctx)->statementContext);
      setState(85);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(86);
    match(WoglacParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

WoglacParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::PragmaStatementContext* WoglacParser::StatementContext::pragmaStatement() {
  return getRuleContext<WoglacParser::PragmaStatementContext>(0);
}

WoglacParser::ParamDefinitionContext* WoglacParser::StatementContext::paramDefinition() {
  return getRuleContext<WoglacParser::ParamDefinitionContext>(0);
}

WoglacParser::BiomeParamDefinitionContext* WoglacParser::StatementContext::biomeParamDefinition() {
  return getRuleContext<WoglacParser::BiomeParamDefinitionContext>(0);
}

WoglacParser::ParamSetStatementContext* WoglacParser::StatementContext::paramSetStatement() {
  return getRuleContext<WoglacParser::ParamSetStatementContext>(0);
}

WoglacParser::BiomeConditionStatementContext* WoglacParser::StatementContext::biomeConditionStatement() {
  return getRuleContext<WoglacParser::BiomeConditionStatementContext>(0);
}

WoglacParser::VariableDefinitionContext* WoglacParser::StatementContext::variableDefinition() {
  return getRuleContext<WoglacParser::VariableDefinitionContext>(0);
}

WoglacParser::RuleExpansionStatementContext* WoglacParser::StatementContext::ruleExpansionStatement() {
  return getRuleContext<WoglacParser::RuleExpansionStatementContext>(0);
}

WoglacParser::ScopeContext* WoglacParser::StatementContext::scope() {
  return getRuleContext<WoglacParser::ScopeContext>(0);
}

WoglacParser::ComponentNodeStatementContext* WoglacParser::StatementContext::componentNodeStatement() {
  return getRuleContext<WoglacParser::ComponentNodeStatementContext>(0);
}

WoglacParser::ComponentBlockStatementContext* WoglacParser::StatementContext::componentBlockStatement() {
  return getRuleContext<WoglacParser::ComponentBlockStatementContext>(0);
}

WoglacParser::ComponentAreaStatementContext* WoglacParser::StatementContext::componentAreaStatement() {
  return getRuleContext<WoglacParser::ComponentAreaStatementContext>(0);
}

WoglacParser::StructureConditionStatementContext* WoglacParser::StatementContext::structureConditionStatement() {
  return getRuleContext<WoglacParser::StructureConditionStatementContext>(0);
}

WoglacParser::ComponentIncludeStatementContext* WoglacParser::StatementContext::componentIncludeStatement() {
  return getRuleContext<WoglacParser::ComponentIncludeStatementContext>(0);
}


size_t WoglacParser::StatementContext::getRuleIndex() const {
  return WoglacParser::RuleStatement;
}

void WoglacParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void WoglacParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

WoglacParser::StatementContext* WoglacParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, WoglacParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(101);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(88);
      pragmaStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(89);
      paramDefinition();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(90);
      biomeParamDefinition();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(91);
      paramSetStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(92);
      biomeConditionStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(93);
      variableDefinition();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(94);
      ruleExpansionStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(95);
      scope();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(96);
      componentNodeStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(97);
      componentBlockStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(98);
      componentAreaStatement();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(99);
      structureConditionStatement();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(100);
      componentIncludeStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScopeContext ------------------------------------------------------------------

WoglacParser::ScopeContext::ScopeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ContentOrSemicolonContext* WoglacParser::ScopeContext::contentOrSemicolon() {
  return getRuleContext<WoglacParser::ContentOrSemicolonContext>(0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ScopeContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}

std::vector<WoglacParser::StatementContext *> WoglacParser::ScopeContext::statement() {
  return getRuleContexts<WoglacParser::StatementContext>();
}

WoglacParser::StatementContext* WoglacParser::ScopeContext::statement(size_t i) {
  return getRuleContext<WoglacParser::StatementContext>(i);
}


size_t WoglacParser::ScopeContext::getRuleIndex() const {
  return WoglacParser::RuleScope;
}

void WoglacParser::ScopeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScope(this);
}

void WoglacParser::ScopeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScope(this);
}

WoglacParser::ScopeContext* WoglacParser::scope() {
  ScopeContext *_localctx = _tracker.createInstance<ScopeContext>(_ctx, getState());
  enterRule(_localctx, 4, WoglacParser::RuleScope);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(118);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WoglacParser::T__0:
      case WoglacParser::T__1:
      case WoglacParser::T__2:
      case WoglacParser::T__3:
      case WoglacParser::T__4: {
        enterOuterAlt(_localctx, 1);
        setState(104);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == WoglacParser::T__0) {
          setState(103);
          antlrcpp::downCast<ScopeContext *>(_localctx)->extend = match(WoglacParser::T__0);
        }
        setState(106);
        antlrcpp::downCast<ScopeContext *>(_localctx)->type = _input->LT(1);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << WoglacParser::T__1)
          | (1ULL << WoglacParser::T__2)
          | (1ULL << WoglacParser::T__3)
          | (1ULL << WoglacParser::T__4))) != 0))) {
          antlrcpp::downCast<ScopeContext *>(_localctx)->type = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(107);
        antlrcpp::downCast<ScopeContext *>(_localctx)->id = extendedIdentifier();
        setState(108);
        contentOrSemicolon();
        break;
      }

      case WoglacParser::T__5: {
        enterOuterAlt(_localctx, 2);
        setState(110);
        match(WoglacParser::T__5);
        setState(114);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << WoglacParser::T__0)
          | (1ULL << WoglacParser::T__1)
          | (1ULL << WoglacParser::T__2)
          | (1ULL << WoglacParser::T__3)
          | (1ULL << WoglacParser::T__4)
          | (1ULL << WoglacParser::T__5)
          | (1ULL << WoglacParser::T__8)
          | (1ULL << WoglacParser::T__10)
          | (1ULL << WoglacParser::T__11)
          | (1ULL << WoglacParser::T__13)
          | (1ULL << WoglacParser::T__20)
          | (1ULL << WoglacParser::T__26)
          | (1ULL << WoglacParser::T__29)
          | (1ULL << WoglacParser::Type))) != 0)) {
          setState(111);
          antlrcpp::downCast<ScopeContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ScopeContext *>(_localctx)->content.push_back(antlrcpp::downCast<ScopeContext *>(_localctx)->statementContext);
          setState(116);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(117);
        match(WoglacParser::T__6);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContentOrSemicolonContext ------------------------------------------------------------------

WoglacParser::ContentOrSemicolonContext::ContentOrSemicolonContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::StatementContext *> WoglacParser::ContentOrSemicolonContext::statement() {
  return getRuleContexts<WoglacParser::StatementContext>();
}

WoglacParser::StatementContext* WoglacParser::ContentOrSemicolonContext::statement(size_t i) {
  return getRuleContext<WoglacParser::StatementContext>(i);
}


size_t WoglacParser::ContentOrSemicolonContext::getRuleIndex() const {
  return WoglacParser::RuleContentOrSemicolon;
}

void WoglacParser::ContentOrSemicolonContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContentOrSemicolon(this);
}

void WoglacParser::ContentOrSemicolonContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContentOrSemicolon(this);
}

WoglacParser::ContentOrSemicolonContext* WoglacParser::contentOrSemicolon() {
  ContentOrSemicolonContext *_localctx = _tracker.createInstance<ContentOrSemicolonContext>(_ctx, getState());
  enterRule(_localctx, 6, WoglacParser::RuleContentOrSemicolon);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(129);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WoglacParser::T__5: {
        enterOuterAlt(_localctx, 1);
        setState(120);
        match(WoglacParser::T__5);
        setState(124);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << WoglacParser::T__0)
          | (1ULL << WoglacParser::T__1)
          | (1ULL << WoglacParser::T__2)
          | (1ULL << WoglacParser::T__3)
          | (1ULL << WoglacParser::T__4)
          | (1ULL << WoglacParser::T__5)
          | (1ULL << WoglacParser::T__8)
          | (1ULL << WoglacParser::T__10)
          | (1ULL << WoglacParser::T__11)
          | (1ULL << WoglacParser::T__13)
          | (1ULL << WoglacParser::T__20)
          | (1ULL << WoglacParser::T__26)
          | (1ULL << WoglacParser::T__29)
          | (1ULL << WoglacParser::Type))) != 0)) {
          setState(121);
          antlrcpp::downCast<ContentOrSemicolonContext *>(_localctx)->statementContext = statement();
          antlrcpp::downCast<ContentOrSemicolonContext *>(_localctx)->content.push_back(antlrcpp::downCast<ContentOrSemicolonContext *>(_localctx)->statementContext);
          setState(126);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(127);
        match(WoglacParser::T__6);
        break;
      }

      case WoglacParser::T__7: {
        enterOuterAlt(_localctx, 2);
        setState(128);
        match(WoglacParser::T__7);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PragmaStatementContext ------------------------------------------------------------------

WoglacParser::PragmaStatementContext::PragmaStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::PragmaStatementContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}

WoglacParser::LiteralExpressionContext* WoglacParser::PragmaStatementContext::literalExpression() {
  return getRuleContext<WoglacParser::LiteralExpressionContext>(0);
}

tree::TerminalNode* WoglacParser::PragmaStatementContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}


size_t WoglacParser::PragmaStatementContext::getRuleIndex() const {
  return WoglacParser::RulePragmaStatement;
}

void WoglacParser::PragmaStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPragmaStatement(this);
}

void WoglacParser::PragmaStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPragmaStatement(this);
}

WoglacParser::PragmaStatementContext* WoglacParser::pragmaStatement() {
  PragmaStatementContext *_localctx = _tracker.createInstance<PragmaStatementContext>(_ctx, getState());
  enterRule(_localctx, 8, WoglacParser::RulePragmaStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(131);
    match(WoglacParser::T__8);
    setState(132);
    antlrcpp::downCast<PragmaStatementContext *>(_localctx)->id = extendedIdentifier();
    setState(138);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__9) {
      setState(133);
      match(WoglacParser::T__9);
      setState(136);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case WoglacParser::T__27:
        case WoglacParser::T__35:
        case WoglacParser::BlockLiteral:
        case WoglacParser::BoolLiteral:
        case WoglacParser::StringLiteral:
        case WoglacParser::NumericLiteral: {
          setState(134);
          antlrcpp::downCast<PragmaStatementContext *>(_localctx)->valLit = literalExpression();
          break;
        }

        case WoglacParser::Identifier: {
          setState(135);
          antlrcpp::downCast<PragmaStatementContext *>(_localctx)->valId = match(WoglacParser::Identifier);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
    }
    setState(140);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDefinitionContext ------------------------------------------------------------------

WoglacParser::VariableDefinitionContext::VariableDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::VariableDefinitionContext::Type() {
  return getToken(WoglacParser::Type, 0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::VariableDefinitionContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}

WoglacParser::ExpressionContext* WoglacParser::VariableDefinitionContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}


size_t WoglacParser::VariableDefinitionContext::getRuleIndex() const {
  return WoglacParser::RuleVariableDefinition;
}

void WoglacParser::VariableDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDefinition(this);
}

void WoglacParser::VariableDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDefinition(this);
}

WoglacParser::VariableDefinitionContext* WoglacParser::variableDefinition() {
  VariableDefinitionContext *_localctx = _tracker.createInstance<VariableDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 10, WoglacParser::RuleVariableDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__10) {
      setState(142);
      antlrcpp::downCast<VariableDefinitionContext *>(_localctx)->exportFlag = match(WoglacParser::T__10);
    }
    setState(145);
    antlrcpp::downCast<VariableDefinitionContext *>(_localctx)->type = match(WoglacParser::Type);
    setState(146);
    antlrcpp::downCast<VariableDefinitionContext *>(_localctx)->id = extendedIdentifier();
    setState(147);
    match(WoglacParser::T__9);
    setState(148);
    antlrcpp::downCast<VariableDefinitionContext *>(_localctx)->val = expression();
    setState(149);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamDefinitionContext ------------------------------------------------------------------

WoglacParser::ParamDefinitionContext::ParamDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::ParamDefinitionContext::Type() {
  return getToken(WoglacParser::Type, 0);
}

tree::TerminalNode* WoglacParser::ParamDefinitionContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}

WoglacParser::ExpressionContext* WoglacParser::ParamDefinitionContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ParamDefinitionContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}


size_t WoglacParser::ParamDefinitionContext::getRuleIndex() const {
  return WoglacParser::RuleParamDefinition;
}

void WoglacParser::ParamDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParamDefinition(this);
}

void WoglacParser::ParamDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParamDefinition(this);
}

WoglacParser::ParamDefinitionContext* WoglacParser::paramDefinition() {
  ParamDefinitionContext *_localctx = _tracker.createInstance<ParamDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 12, WoglacParser::RuleParamDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__2

    || _la == WoglacParser::T__3) {
      setState(151);
      antlrcpp::downCast<ParamDefinitionContext *>(_localctx)->targetType = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == WoglacParser::T__2

      || _la == WoglacParser::T__3)) {
        antlrcpp::downCast<ParamDefinitionContext *>(_localctx)->targetType = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(153);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::Identifier) {
        setState(152);
        antlrcpp::downCast<ParamDefinitionContext *>(_localctx)->target = extendedIdentifier();
      }
    }
    setState(157);
    match(WoglacParser::T__11);
    setState(158);
    antlrcpp::downCast<ParamDefinitionContext *>(_localctx)->type = match(WoglacParser::Type);
    setState(159);
    antlrcpp::downCast<ParamDefinitionContext *>(_localctx)->id = match(WoglacParser::Identifier);
    setState(162);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__12) {
      setState(160);
      match(WoglacParser::T__12);
      setState(161);
      antlrcpp::downCast<ParamDefinitionContext *>(_localctx)->defaultValue = expression();
    }
    setState(164);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BiomeParamDefinitionContext ------------------------------------------------------------------

WoglacParser::BiomeParamDefinitionContext::BiomeParamDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::BiomeParamDefinitionContext::Type() {
  return getToken(WoglacParser::Type, 0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::BiomeParamDefinitionContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}

WoglacParser::ExpressionContext* WoglacParser::BiomeParamDefinitionContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}


size_t WoglacParser::BiomeParamDefinitionContext::getRuleIndex() const {
  return WoglacParser::RuleBiomeParamDefinition;
}

void WoglacParser::BiomeParamDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBiomeParamDefinition(this);
}

void WoglacParser::BiomeParamDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBiomeParamDefinition(this);
}

WoglacParser::BiomeParamDefinitionContext* WoglacParser::biomeParamDefinition() {
  BiomeParamDefinitionContext *_localctx = _tracker.createInstance<BiomeParamDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 14, WoglacParser::RuleBiomeParamDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(166);
    match(WoglacParser::T__4);
    setState(167);
    match(WoglacParser::T__11);
    setState(168);
    antlrcpp::downCast<BiomeParamDefinitionContext *>(_localctx)->type = match(WoglacParser::Type);
    setState(169);
    antlrcpp::downCast<BiomeParamDefinitionContext *>(_localctx)->id = extendedIdentifier();
    setState(170);
    match(WoglacParser::T__12);
    setState(171);
    antlrcpp::downCast<BiomeParamDefinitionContext *>(_localctx)->defaultValue = expression();
    setState(172);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamSetStatementContext ------------------------------------------------------------------

WoglacParser::ParamSetStatementContext::ParamSetStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::ExtendedIdentifierContext *> WoglacParser::ParamSetStatementContext::extendedIdentifier() {
  return getRuleContexts<WoglacParser::ExtendedIdentifierContext>();
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ParamSetStatementContext::extendedIdentifier(size_t i) {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(i);
}

WoglacParser::ExpressionContext* WoglacParser::ParamSetStatementContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}


size_t WoglacParser::ParamSetStatementContext::getRuleIndex() const {
  return WoglacParser::RuleParamSetStatement;
}

void WoglacParser::ParamSetStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParamSetStatement(this);
}

void WoglacParser::ParamSetStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParamSetStatement(this);
}

WoglacParser::ParamSetStatementContext* WoglacParser::paramSetStatement() {
  ParamSetStatementContext *_localctx = _tracker.createInstance<ParamSetStatementContext>(_ctx, getState());
  enterRule(_localctx, 16, WoglacParser::RuleParamSetStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WoglacParser::T__2)
      | (1ULL << WoglacParser::T__3)
      | (1ULL << WoglacParser::T__4))) != 0)) {
      setState(174);
      antlrcpp::downCast<ParamSetStatementContext *>(_localctx)->targetType = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << WoglacParser::T__2)
        | (1ULL << WoglacParser::T__3)
        | (1ULL << WoglacParser::T__4))) != 0))) {
        antlrcpp::downCast<ParamSetStatementContext *>(_localctx)->targetType = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(175);
      antlrcpp::downCast<ParamSetStatementContext *>(_localctx)->target = extendedIdentifier();
    }
    setState(178);
    match(WoglacParser::T__11);
    setState(179);
    antlrcpp::downCast<ParamSetStatementContext *>(_localctx)->param = extendedIdentifier();
    setState(180);
    match(WoglacParser::T__9);
    setState(181);
    antlrcpp::downCast<ParamSetStatementContext *>(_localctx)->value = expression();
    setState(182);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BiomeConditionStatementContext ------------------------------------------------------------------

WoglacParser::BiomeConditionStatementContext::BiomeConditionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::ExtendedIdentifierContext *> WoglacParser::BiomeConditionStatementContext::extendedIdentifier() {
  return getRuleContexts<WoglacParser::ExtendedIdentifierContext>();
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::BiomeConditionStatementContext::extendedIdentifier(size_t i) {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(i);
}

std::vector<tree::TerminalNode *> WoglacParser::BiomeConditionStatementContext::NumericLiteral() {
  return getTokens(WoglacParser::NumericLiteral);
}

tree::TerminalNode* WoglacParser::BiomeConditionStatementContext::NumericLiteral(size_t i) {
  return getToken(WoglacParser::NumericLiteral, i);
}


size_t WoglacParser::BiomeConditionStatementContext::getRuleIndex() const {
  return WoglacParser::RuleBiomeConditionStatement;
}

void WoglacParser::BiomeConditionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBiomeConditionStatement(this);
}

void WoglacParser::BiomeConditionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBiomeConditionStatement(this);
}

WoglacParser::BiomeConditionStatementContext* WoglacParser::biomeConditionStatement() {
  BiomeConditionStatementContext *_localctx = _tracker.createInstance<BiomeConditionStatementContext>(_ctx, getState());
  enterRule(_localctx, 18, WoglacParser::RuleBiomeConditionStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(188);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__4) {
      setState(184);
      match(WoglacParser::T__4);
      setState(186);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::Identifier) {
        setState(185);
        antlrcpp::downCast<BiomeConditionStatementContext *>(_localctx)->target = extendedIdentifier();
      }
    }
    setState(190);
    match(WoglacParser::T__13);
    setState(191);
    antlrcpp::downCast<BiomeConditionStatementContext *>(_localctx)->param = extendedIdentifier();
    setState(192);
    match(WoglacParser::T__9);
    setState(193);
    antlrcpp::downCast<BiomeConditionStatementContext *>(_localctx)->mean = match(WoglacParser::NumericLiteral);
    setState(194);
    match(WoglacParser::T__14);
    setState(195);
    antlrcpp::downCast<BiomeConditionStatementContext *>(_localctx)->dev = match(WoglacParser::NumericLiteral);
    setState(196);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructureConditionStatementContext ------------------------------------------------------------------

WoglacParser::StructureConditionStatementContext::StructureConditionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ExpressionContext* WoglacParser::StructureConditionStatementContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::StructureConditionStatementContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}


size_t WoglacParser::StructureConditionStatementContext::getRuleIndex() const {
  return WoglacParser::RuleStructureConditionStatement;
}

void WoglacParser::StructureConditionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructureConditionStatement(this);
}

void WoglacParser::StructureConditionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructureConditionStatement(this);
}

WoglacParser::StructureConditionStatementContext* WoglacParser::structureConditionStatement() {
  StructureConditionStatementContext *_localctx = _tracker.createInstance<StructureConditionStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, WoglacParser::RuleStructureConditionStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(202);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__2

    || _la == WoglacParser::T__3) {
      setState(198);
      antlrcpp::downCast<StructureConditionStatementContext *>(_localctx)->targetType = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == WoglacParser::T__2

      || _la == WoglacParser::T__3)) {
        antlrcpp::downCast<StructureConditionStatementContext *>(_localctx)->targetType = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(200);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::Identifier) {
        setState(199);
        antlrcpp::downCast<StructureConditionStatementContext *>(_localctx)->target = extendedIdentifier();
      }
    }
    setState(204);
    match(WoglacParser::T__13);
    setState(205);
    antlrcpp::downCast<StructureConditionStatementContext *>(_localctx)->cond = expression();
    setState(206);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RuleExpansionStatementContext ------------------------------------------------------------------

WoglacParser::RuleExpansionStatementContext::RuleExpansionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ContentOrSemicolonContext* WoglacParser::RuleExpansionStatementContext::contentOrSemicolon() {
  return getRuleContext<WoglacParser::ContentOrSemicolonContext>(0);
}

std::vector<WoglacParser::ExtendedIdentifierContext *> WoglacParser::RuleExpansionStatementContext::extendedIdentifier() {
  return getRuleContexts<WoglacParser::ExtendedIdentifierContext>();
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::RuleExpansionStatementContext::extendedIdentifier(size_t i) {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(i);
}

std::vector<tree::TerminalNode *> WoglacParser::RuleExpansionStatementContext::NumericLiteral() {
  return getTokens(WoglacParser::NumericLiteral);
}

tree::TerminalNode* WoglacParser::RuleExpansionStatementContext::NumericLiteral(size_t i) {
  return getToken(WoglacParser::NumericLiteral, i);
}

tree::TerminalNode* WoglacParser::RuleExpansionStatementContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}


size_t WoglacParser::RuleExpansionStatementContext::getRuleIndex() const {
  return WoglacParser::RuleRuleExpansionStatement;
}

void WoglacParser::RuleExpansionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuleExpansionStatement(this);
}

void WoglacParser::RuleExpansionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuleExpansionStatement(this);
}

WoglacParser::RuleExpansionStatementContext* WoglacParser::ruleExpansionStatement() {
  RuleExpansionStatementContext *_localctx = _tracker.createInstance<RuleExpansionStatementContext>(_ctx, getState());
  enterRule(_localctx, 22, WoglacParser::RuleRuleExpansionStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(208);
    match(WoglacParser::T__2);
    setState(210);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::Identifier) {
      setState(209);
      antlrcpp::downCast<RuleExpansionStatementContext *>(_localctx)->target = extendedIdentifier();
    }
    setState(212);
    match(WoglacParser::T__15);
    setState(219);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WoglacParser::Identifier: {
        setState(213);
        antlrcpp::downCast<RuleExpansionStatementContext *>(_localctx)->expansionTarget = extendedIdentifier();
        setState(216);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == WoglacParser::T__16) {
          setState(214);
          match(WoglacParser::T__16);
          setState(215);
          antlrcpp::downCast<RuleExpansionStatementContext *>(_localctx)->node = match(WoglacParser::Identifier);
        }
        break;
      }

      case WoglacParser::T__17: {
        setState(218);
        match(WoglacParser::T__17);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(223);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__18) {
      setState(221);
      match(WoglacParser::T__18);
      setState(222);
      antlrcpp::downCast<RuleExpansionStatementContext *>(_localctx)->priority = match(WoglacParser::NumericLiteral);
    }
    setState(227);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__19) {
      setState(225);
      match(WoglacParser::T__19);
      setState(226);
      antlrcpp::downCast<RuleExpansionStatementContext *>(_localctx)->probabilityRatio = match(WoglacParser::NumericLiteral);
    }
    setState(229);
    antlrcpp::downCast<RuleExpansionStatementContext *>(_localctx)->content = contentOrSemicolon();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentNodeStatementContext ------------------------------------------------------------------

WoglacParser::ComponentNodeStatementContext::ComponentNodeStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::PositionExpressionContext* WoglacParser::ComponentNodeStatementContext::positionExpression() {
  return getRuleContext<WoglacParser::PositionExpressionContext>(0);
}

WoglacParser::ComponentNodeStatementCommonPartContext* WoglacParser::ComponentNodeStatementContext::componentNodeStatementCommonPart() {
  return getRuleContext<WoglacParser::ComponentNodeStatementCommonPartContext>(0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ComponentNodeStatementContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}


size_t WoglacParser::ComponentNodeStatementContext::getRuleIndex() const {
  return WoglacParser::RuleComponentNodeStatement;
}

void WoglacParser::ComponentNodeStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentNodeStatement(this);
}

void WoglacParser::ComponentNodeStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentNodeStatement(this);
}

WoglacParser::ComponentNodeStatementContext* WoglacParser::componentNodeStatement() {
  ComponentNodeStatementContext *_localctx = _tracker.createInstance<ComponentNodeStatementContext>(_ctx, getState());
  enterRule(_localctx, 24, WoglacParser::RuleComponentNodeStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(233);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__3) {
      setState(231);
      match(WoglacParser::T__3);
      setState(232);
      antlrcpp::downCast<ComponentNodeStatementContext *>(_localctx)->target = extendedIdentifier();
    }
    setState(235);
    match(WoglacParser::T__20);
    setState(236);
    antlrcpp::downCast<ComponentNodeStatementContext *>(_localctx)->pos = positionExpression();
    setState(237);
    antlrcpp::downCast<ComponentNodeStatementContext *>(_localctx)->cmn = componentNodeStatementCommonPart();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentNodeStatementCommonPartContext ------------------------------------------------------------------

WoglacParser::ComponentNodeStatementCommonPartContext::ComponentNodeStatementCommonPartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ContentOrSemicolonContext* WoglacParser::ComponentNodeStatementCommonPartContext::contentOrSemicolon() {
  return getRuleContext<WoglacParser::ContentOrSemicolonContext>(0);
}

WoglacParser::ComponentNodePropertiesSectionContext* WoglacParser::ComponentNodeStatementCommonPartContext::componentNodePropertiesSection() {
  return getRuleContext<WoglacParser::ComponentNodePropertiesSectionContext>(0);
}

tree::TerminalNode* WoglacParser::ComponentNodeStatementCommonPartContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ComponentNodeStatementCommonPartContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}


size_t WoglacParser::ComponentNodeStatementCommonPartContext::getRuleIndex() const {
  return WoglacParser::RuleComponentNodeStatementCommonPart;
}

void WoglacParser::ComponentNodeStatementCommonPartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentNodeStatementCommonPart(this);
}

void WoglacParser::ComponentNodeStatementCommonPartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentNodeStatementCommonPart(this);
}

WoglacParser::ComponentNodeStatementCommonPartContext* WoglacParser::componentNodeStatementCommonPart() {
  ComponentNodeStatementCommonPartContext *_localctx = _tracker.createInstance<ComponentNodeStatementCommonPartContext>(_ctx, getState());
  enterRule(_localctx, 26, WoglacParser::RuleComponentNodeStatementCommonPart);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(240);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__21) {
      setState(239);
      antlrcpp::downCast<ComponentNodeStatementCommonPartContext *>(_localctx)->prop = componentNodePropertiesSection();
    }
    setState(243);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::Identifier) {
      setState(242);
      antlrcpp::downCast<ComponentNodeStatementCommonPartContext *>(_localctx)->group = match(WoglacParser::Identifier);
    }
    setState(247);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__15) {
      setState(245);
      match(WoglacParser::T__15);
      setState(246);
      antlrcpp::downCast<ComponentNodeStatementCommonPartContext *>(_localctx)->rule_ = extendedIdentifier();
    }
    setState(249);
    contentOrSemicolon();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentNodePropertiesSectionContext ------------------------------------------------------------------

WoglacParser::ComponentNodePropertiesSectionContext::ComponentNodePropertiesSectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::ComponentNodeOrientationExpressionContext *> WoglacParser::ComponentNodePropertiesSectionContext::componentNodeOrientationExpression() {
  return getRuleContexts<WoglacParser::ComponentNodeOrientationExpressionContext>();
}

WoglacParser::ComponentNodeOrientationExpressionContext* WoglacParser::ComponentNodePropertiesSectionContext::componentNodeOrientationExpression(size_t i) {
  return getRuleContext<WoglacParser::ComponentNodeOrientationExpressionContext>(i);
}


size_t WoglacParser::ComponentNodePropertiesSectionContext::getRuleIndex() const {
  return WoglacParser::RuleComponentNodePropertiesSection;
}

void WoglacParser::ComponentNodePropertiesSectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentNodePropertiesSection(this);
}

void WoglacParser::ComponentNodePropertiesSectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentNodePropertiesSection(this);
}

WoglacParser::ComponentNodePropertiesSectionContext* WoglacParser::componentNodePropertiesSection() {
  ComponentNodePropertiesSectionContext *_localctx = _tracker.createInstance<ComponentNodePropertiesSectionContext>(_ctx, getState());
  enterRule(_localctx, 28, WoglacParser::RuleComponentNodePropertiesSection);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(251);
    match(WoglacParser::T__21);
    setState(253);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__9) {
      setState(252);
      antlrcpp::downCast<ComponentNodePropertiesSectionContext *>(_localctx)->notAdjacent = match(WoglacParser::T__9);
    }
    setState(256);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__22) {
      setState(255);
      antlrcpp::downCast<ComponentNodePropertiesSectionContext *>(_localctx)->horizontalEdge = match(WoglacParser::T__22);
    }
    setState(259);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__23) {
      setState(258);
      antlrcpp::downCast<ComponentNodePropertiesSectionContext *>(_localctx)->verticalEdge = match(WoglacParser::T__23);
    }
    setState(261);
    antlrcpp::downCast<ComponentNodePropertiesSectionContext *>(_localctx)->ori = componentNodeOrientationExpression();
    setState(263);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::Identifier) {
      setState(262);
      antlrcpp::downCast<ComponentNodePropertiesSectionContext *>(_localctx)->ori2 = componentNodeOrientationExpression();
    }
    setState(265);
    match(WoglacParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentNodeOrientationExpressionContext ------------------------------------------------------------------

WoglacParser::ComponentNodeOrientationExpressionContext::ComponentNodeOrientationExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::ComponentNodeOrientationExpressionContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}


size_t WoglacParser::ComponentNodeOrientationExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleComponentNodeOrientationExpression;
}

void WoglacParser::ComponentNodeOrientationExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentNodeOrientationExpression(this);
}

void WoglacParser::ComponentNodeOrientationExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentNodeOrientationExpression(this);
}

WoglacParser::ComponentNodeOrientationExpressionContext* WoglacParser::componentNodeOrientationExpression() {
  ComponentNodeOrientationExpressionContext *_localctx = _tracker.createInstance<ComponentNodeOrientationExpressionContext>(_ctx, getState());
  enterRule(_localctx, 30, WoglacParser::RuleComponentNodeOrientationExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(267);
    antlrcpp::downCast<ComponentNodeOrientationExpressionContext *>(_localctx)->dir = match(WoglacParser::Identifier);
    setState(268);
    antlrcpp::downCast<ComponentNodeOrientationExpressionContext *>(_localctx)->sign = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == WoglacParser::T__23

    || _la == WoglacParser::T__25)) {
      antlrcpp::downCast<ComponentNodeOrientationExpressionContext *>(_localctx)->sign = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentAreaStatementContext ------------------------------------------------------------------

WoglacParser::ComponentAreaStatementContext::ComponentAreaStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::PositionExpressionContext *> WoglacParser::ComponentAreaStatementContext::positionExpression() {
  return getRuleContexts<WoglacParser::PositionExpressionContext>();
}

WoglacParser::PositionExpressionContext* WoglacParser::ComponentAreaStatementContext::positionExpression(size_t i) {
  return getRuleContext<WoglacParser::PositionExpressionContext>(i);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ComponentAreaStatementContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}

tree::TerminalNode* WoglacParser::ComponentAreaStatementContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}


size_t WoglacParser::ComponentAreaStatementContext::getRuleIndex() const {
  return WoglacParser::RuleComponentAreaStatement;
}

void WoglacParser::ComponentAreaStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentAreaStatement(this);
}

void WoglacParser::ComponentAreaStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentAreaStatement(this);
}

WoglacParser::ComponentAreaStatementContext* WoglacParser::componentAreaStatement() {
  ComponentAreaStatementContext *_localctx = _tracker.createInstance<ComponentAreaStatementContext>(_ctx, getState());
  enterRule(_localctx, 32, WoglacParser::RuleComponentAreaStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(272);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__3) {
      setState(270);
      match(WoglacParser::T__3);
      setState(271);
      antlrcpp::downCast<ComponentAreaStatementContext *>(_localctx)->target = extendedIdentifier();
    }
    setState(274);
    match(WoglacParser::T__26);
    setState(275);
    antlrcpp::downCast<ComponentAreaStatementContext *>(_localctx)->startPos = positionExpression();
    setState(276);
    antlrcpp::downCast<ComponentAreaStatementContext *>(_localctx)->endPos = positionExpression();
    setState(288);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__21) {
      setState(277);
      match(WoglacParser::T__21);
      setState(279);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::T__27) {
        setState(278);
        antlrcpp::downCast<ComponentAreaStatementContext *>(_localctx)->canOverlap = match(WoglacParser::T__27);
      }
      setState(282);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::T__18) {
        setState(281);
        antlrcpp::downCast<ComponentAreaStatementContext *>(_localctx)->mustOverlap = match(WoglacParser::T__18);
      }
      setState(285);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::T__28) {
        setState(284);
        antlrcpp::downCast<ComponentAreaStatementContext *>(_localctx)->isVirtual = match(WoglacParser::T__28);
      }
      setState(287);
      match(WoglacParser::T__24);
    }
    setState(291);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::Identifier) {
      setState(290);
      antlrcpp::downCast<ComponentAreaStatementContext *>(_localctx)->name = match(WoglacParser::Identifier);
    }
    setState(293);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentBlockStatementContext ------------------------------------------------------------------

WoglacParser::ComponentBlockStatementContext::ComponentBlockStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::PositionExpressionContext *> WoglacParser::ComponentBlockStatementContext::positionExpression() {
  return getRuleContexts<WoglacParser::PositionExpressionContext>();
}

WoglacParser::PositionExpressionContext* WoglacParser::ComponentBlockStatementContext::positionExpression(size_t i) {
  return getRuleContext<WoglacParser::PositionExpressionContext>(i);
}

WoglacParser::ExpressionContext* WoglacParser::ComponentBlockStatementContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::ComponentBlockStatementContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}


size_t WoglacParser::ComponentBlockStatementContext::getRuleIndex() const {
  return WoglacParser::RuleComponentBlockStatement;
}

void WoglacParser::ComponentBlockStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentBlockStatement(this);
}

void WoglacParser::ComponentBlockStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentBlockStatement(this);
}

WoglacParser::ComponentBlockStatementContext* WoglacParser::componentBlockStatement() {
  ComponentBlockStatementContext *_localctx = _tracker.createInstance<ComponentBlockStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, WoglacParser::RuleComponentBlockStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(297);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__3) {
      setState(295);
      match(WoglacParser::T__3);
      setState(296);
      antlrcpp::downCast<ComponentBlockStatementContext *>(_localctx)->target = extendedIdentifier();
    }
    setState(299);
    match(WoglacParser::T__29);
    setState(300);
    antlrcpp::downCast<ComponentBlockStatementContext *>(_localctx)->startPos = positionExpression();
    setState(302);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WoglacParser::T__21) {
      setState(301);
      antlrcpp::downCast<ComponentBlockStatementContext *>(_localctx)->endPos = positionExpression();
    }
    setState(304);
    match(WoglacParser::T__9);
    setState(305);
    antlrcpp::downCast<ComponentBlockStatementContext *>(_localctx)->val = expression();
    setState(306);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentIncludeStatementContext ------------------------------------------------------------------

WoglacParser::ComponentIncludeStatementContext::ComponentIncludeStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::ComponentIncludeStatementContext::StringLiteral() {
  return getToken(WoglacParser::StringLiteral, 0);
}

std::vector<WoglacParser::ComponentIncludeStatementParamContext *> WoglacParser::ComponentIncludeStatementContext::componentIncludeStatementParam() {
  return getRuleContexts<WoglacParser::ComponentIncludeStatementParamContext>();
}

WoglacParser::ComponentIncludeStatementParamContext* WoglacParser::ComponentIncludeStatementContext::componentIncludeStatementParam(size_t i) {
  return getRuleContext<WoglacParser::ComponentIncludeStatementParamContext>(i);
}


size_t WoglacParser::ComponentIncludeStatementContext::getRuleIndex() const {
  return WoglacParser::RuleComponentIncludeStatement;
}

void WoglacParser::ComponentIncludeStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentIncludeStatement(this);
}

void WoglacParser::ComponentIncludeStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentIncludeStatement(this);
}

WoglacParser::ComponentIncludeStatementContext* WoglacParser::componentIncludeStatement() {
  ComponentIncludeStatementContext *_localctx = _tracker.createInstance<ComponentIncludeStatementContext>(_ctx, getState());
  enterRule(_localctx, 36, WoglacParser::RuleComponentIncludeStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(308);
    match(WoglacParser::T__3);
    setState(309);
    match(WoglacParser::T__30);
    setState(310);
    antlrcpp::downCast<ComponentIncludeStatementContext *>(_localctx)->file = match(WoglacParser::StringLiteral);
    setState(311);
    match(WoglacParser::T__5);
    setState(315);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == WoglacParser::NumericLiteral) {
      setState(312);
      antlrcpp::downCast<ComponentIncludeStatementContext *>(_localctx)->componentIncludeStatementParamContext = componentIncludeStatementParam();
      antlrcpp::downCast<ComponentIncludeStatementContext *>(_localctx)->content.push_back(antlrcpp::downCast<ComponentIncludeStatementContext *>(_localctx)->componentIncludeStatementParamContext);
      setState(317);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(318);
    match(WoglacParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentIncludeStatementParamContext ------------------------------------------------------------------

WoglacParser::ComponentIncludeStatementParamContext::ComponentIncludeStatementParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ComponentIncludeStatementBlockParamContext* WoglacParser::ComponentIncludeStatementParamContext::componentIncludeStatementBlockParam() {
  return getRuleContext<WoglacParser::ComponentIncludeStatementBlockParamContext>(0);
}

WoglacParser::ComponentIncludeStatementNodeParamContext* WoglacParser::ComponentIncludeStatementParamContext::componentIncludeStatementNodeParam() {
  return getRuleContext<WoglacParser::ComponentIncludeStatementNodeParamContext>(0);
}


size_t WoglacParser::ComponentIncludeStatementParamContext::getRuleIndex() const {
  return WoglacParser::RuleComponentIncludeStatementParam;
}

void WoglacParser::ComponentIncludeStatementParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentIncludeStatementParam(this);
}

void WoglacParser::ComponentIncludeStatementParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentIncludeStatementParam(this);
}

WoglacParser::ComponentIncludeStatementParamContext* WoglacParser::componentIncludeStatementParam() {
  ComponentIncludeStatementParamContext *_localctx = _tracker.createInstance<ComponentIncludeStatementParamContext>(_ctx, getState());
  enterRule(_localctx, 38, WoglacParser::RuleComponentIncludeStatementParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(322);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(320);
      antlrcpp::downCast<ComponentIncludeStatementParamContext *>(_localctx)->block = componentIncludeStatementBlockParam();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(321);
      antlrcpp::downCast<ComponentIncludeStatementParamContext *>(_localctx)->node = componentIncludeStatementNodeParam();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentIncludeStatementBlockParamContext ------------------------------------------------------------------

WoglacParser::ComponentIncludeStatementBlockParamContext::ComponentIncludeStatementBlockParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::ComponentIncludeStatementBlockParamContext::NumericLiteral() {
  return getToken(WoglacParser::NumericLiteral, 0);
}

WoglacParser::ExpressionContext* WoglacParser::ComponentIncludeStatementBlockParamContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}


size_t WoglacParser::ComponentIncludeStatementBlockParamContext::getRuleIndex() const {
  return WoglacParser::RuleComponentIncludeStatementBlockParam;
}

void WoglacParser::ComponentIncludeStatementBlockParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentIncludeStatementBlockParam(this);
}

void WoglacParser::ComponentIncludeStatementBlockParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentIncludeStatementBlockParam(this);
}

WoglacParser::ComponentIncludeStatementBlockParamContext* WoglacParser::componentIncludeStatementBlockParam() {
  ComponentIncludeStatementBlockParamContext *_localctx = _tracker.createInstance<ComponentIncludeStatementBlockParamContext>(_ctx, getState());
  enterRule(_localctx, 40, WoglacParser::RuleComponentIncludeStatementBlockParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(324);
    antlrcpp::downCast<ComponentIncludeStatementBlockParamContext *>(_localctx)->id = match(WoglacParser::NumericLiteral);
    setState(325);
    match(WoglacParser::T__15);
    setState(326);
    match(WoglacParser::T__29);
    setState(327);
    antlrcpp::downCast<ComponentIncludeStatementBlockParamContext *>(_localctx)->val = expression();
    setState(328);
    match(WoglacParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentIncludeStatementNodeParamContext ------------------------------------------------------------------

WoglacParser::ComponentIncludeStatementNodeParamContext::ComponentIncludeStatementNodeParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::ComponentIncludeStatementNodeParamContext::NumericLiteral() {
  return getToken(WoglacParser::NumericLiteral, 0);
}

WoglacParser::ComponentNodeStatementCommonPartContext* WoglacParser::ComponentIncludeStatementNodeParamContext::componentNodeStatementCommonPart() {
  return getRuleContext<WoglacParser::ComponentNodeStatementCommonPartContext>(0);
}


size_t WoglacParser::ComponentIncludeStatementNodeParamContext::getRuleIndex() const {
  return WoglacParser::RuleComponentIncludeStatementNodeParam;
}

void WoglacParser::ComponentIncludeStatementNodeParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponentIncludeStatementNodeParam(this);
}

void WoglacParser::ComponentIncludeStatementNodeParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponentIncludeStatementNodeParam(this);
}

WoglacParser::ComponentIncludeStatementNodeParamContext* WoglacParser::componentIncludeStatementNodeParam() {
  ComponentIncludeStatementNodeParamContext *_localctx = _tracker.createInstance<ComponentIncludeStatementNodeParamContext>(_ctx, getState());
  enterRule(_localctx, 42, WoglacParser::RuleComponentIncludeStatementNodeParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(330);
    antlrcpp::downCast<ComponentIncludeStatementNodeParamContext *>(_localctx)->id = match(WoglacParser::NumericLiteral);
    setState(331);
    match(WoglacParser::T__15);
    setState(332);
    match(WoglacParser::T__20);
    setState(333);
    antlrcpp::downCast<ComponentIncludeStatementNodeParamContext *>(_localctx)->com = componentNodeStatementCommonPart();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PositionExpressionContext ------------------------------------------------------------------

WoglacParser::PositionExpressionContext::PositionExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::ExpressionContext *> WoglacParser::PositionExpressionContext::expression() {
  return getRuleContexts<WoglacParser::ExpressionContext>();
}

WoglacParser::ExpressionContext* WoglacParser::PositionExpressionContext::expression(size_t i) {
  return getRuleContext<WoglacParser::ExpressionContext>(i);
}


size_t WoglacParser::PositionExpressionContext::getRuleIndex() const {
  return WoglacParser::RulePositionExpression;
}

void WoglacParser::PositionExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPositionExpression(this);
}

void WoglacParser::PositionExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPositionExpression(this);
}

WoglacParser::PositionExpressionContext* WoglacParser::positionExpression() {
  PositionExpressionContext *_localctx = _tracker.createInstance<PositionExpressionContext>(_ctx, getState());
  enterRule(_localctx, 44, WoglacParser::RulePositionExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(335);
    match(WoglacParser::T__21);
    setState(343);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
    case 1: {
      setState(336);
      antlrcpp::downCast<PositionExpressionContext *>(_localctx)->x = expression();
      setState(337);
      match(WoglacParser::T__31);
      setState(338);
      antlrcpp::downCast<PositionExpressionContext *>(_localctx)->y = expression();
      setState(339);
      match(WoglacParser::T__31);
      setState(340);
      antlrcpp::downCast<PositionExpressionContext *>(_localctx)->z = expression();
      break;
    }

    case 2: {
      setState(342);
      antlrcpp::downCast<PositionExpressionContext *>(_localctx)->vec = expression();
      break;
    }

    default:
      break;
    }
    setState(345);
    match(WoglacParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

WoglacParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::TernaryExpressionContext* WoglacParser::ExpressionContext::ternaryExpression() {
  return getRuleContext<WoglacParser::TernaryExpressionContext>(0);
}


size_t WoglacParser::ExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleExpression;
}

void WoglacParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void WoglacParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}

WoglacParser::ExpressionContext* WoglacParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 46, WoglacParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(347);
    antlrcpp::downCast<ExpressionContext *>(_localctx)->e = ternaryExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParentExpressionContext ------------------------------------------------------------------

WoglacParser::ParentExpressionContext::ParentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ExpressionContext* WoglacParser::ParentExpressionContext::expression() {
  return getRuleContext<WoglacParser::ExpressionContext>(0);
}


size_t WoglacParser::ParentExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleParentExpression;
}

void WoglacParser::ParentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParentExpression(this);
}

void WoglacParser::ParentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParentExpression(this);
}

WoglacParser::ParentExpressionContext* WoglacParser::parentExpression() {
  ParentExpressionContext *_localctx = _tracker.createInstance<ParentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 48, WoglacParser::RuleParentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(349);
    match(WoglacParser::T__21);
    setState(350);
    antlrcpp::downCast<ParentExpressionContext *>(_localctx)->e = expression();
    setState(351);
    match(WoglacParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TernaryExpressionContext ------------------------------------------------------------------

WoglacParser::TernaryExpressionContext::TernaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::LogicalExpressionContext *> WoglacParser::TernaryExpressionContext::logicalExpression() {
  return getRuleContexts<WoglacParser::LogicalExpressionContext>();
}

WoglacParser::LogicalExpressionContext* WoglacParser::TernaryExpressionContext::logicalExpression(size_t i) {
  return getRuleContext<WoglacParser::LogicalExpressionContext>(i);
}

WoglacParser::TernaryExpressionContext* WoglacParser::TernaryExpressionContext::ternaryExpression() {
  return getRuleContext<WoglacParser::TernaryExpressionContext>(0);
}


size_t WoglacParser::TernaryExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleTernaryExpression;
}

void WoglacParser::TernaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTernaryExpression(this);
}

void WoglacParser::TernaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTernaryExpression(this);
}

WoglacParser::TernaryExpressionContext* WoglacParser::ternaryExpression() {
  TernaryExpressionContext *_localctx = _tracker.createInstance<TernaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 50, WoglacParser::RuleTernaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(362);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(353);
      antlrcpp::downCast<TernaryExpressionContext *>(_localctx)->base = logicalExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(354);
      antlrcpp::downCast<TernaryExpressionContext *>(_localctx)->condition = logicalExpression();
      setState(355);
      match(WoglacParser::T__28);
      setState(357);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << WoglacParser::T__4)
        | (1ULL << WoglacParser::T__18)
        | (1ULL << WoglacParser::T__21)
        | (1ULL << WoglacParser::T__23)
        | (1ULL << WoglacParser::T__25)
        | (1ULL << WoglacParser::T__27)
        | (1ULL << WoglacParser::T__35)
        | (1ULL << WoglacParser::BlockLiteral)
        | (1ULL << WoglacParser::BoolLiteral)
        | (1ULL << WoglacParser::StringLiteral)
        | (1ULL << WoglacParser::Identifier)
        | (1ULL << WoglacParser::NumericLiteral))) != 0)) {
        setState(356);
        antlrcpp::downCast<TernaryExpressionContext *>(_localctx)->thenBranch = logicalExpression();
      }
      setState(359);
      match(WoglacParser::T__19);
      setState(360);
      antlrcpp::downCast<TernaryExpressionContext *>(_localctx)->elseBranch = ternaryExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalExpressionContext ------------------------------------------------------------------

WoglacParser::LogicalExpressionContext::LogicalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::AndExpressionContext* WoglacParser::LogicalExpressionContext::andExpression() {
  return getRuleContext<WoglacParser::AndExpressionContext>(0);
}

WoglacParser::OrExpressionContext* WoglacParser::LogicalExpressionContext::orExpression() {
  return getRuleContext<WoglacParser::OrExpressionContext>(0);
}


size_t WoglacParser::LogicalExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleLogicalExpression;
}

void WoglacParser::LogicalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalExpression(this);
}

void WoglacParser::LogicalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalExpression(this);
}

WoglacParser::LogicalExpressionContext* WoglacParser::logicalExpression() {
  LogicalExpressionContext *_localctx = _tracker.createInstance<LogicalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 52, WoglacParser::RuleLogicalExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(366);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(364);
      antlrcpp::downCast<LogicalExpressionContext *>(_localctx)->a = andExpression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(365);
      antlrcpp::downCast<LogicalExpressionContext *>(_localctx)->o = orExpression(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AndExpressionContext ------------------------------------------------------------------

WoglacParser::AndExpressionContext::AndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ComparisonExpressionContext* WoglacParser::AndExpressionContext::comparisonExpression() {
  return getRuleContext<WoglacParser::ComparisonExpressionContext>(0);
}

WoglacParser::AndExpressionContext* WoglacParser::AndExpressionContext::andExpression() {
  return getRuleContext<WoglacParser::AndExpressionContext>(0);
}


size_t WoglacParser::AndExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleAndExpression;
}

void WoglacParser::AndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndExpression(this);
}

void WoglacParser::AndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndExpression(this);
}


WoglacParser::AndExpressionContext* WoglacParser::andExpression() {
   return andExpression(0);
}

WoglacParser::AndExpressionContext* WoglacParser::andExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  WoglacParser::AndExpressionContext *_localctx = _tracker.createInstance<AndExpressionContext>(_ctx, parentState);
  WoglacParser::AndExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, WoglacParser::RuleAndExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(369);
    antlrcpp::downCast<AndExpressionContext *>(_localctx)->base = comparisonExpression();
    _ctx->stop = _input->LT(-1);
    setState(376);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<AndExpressionContext>(parentContext, parentState);
        _localctx->left = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleAndExpression);
        setState(371);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(372);
        match(WoglacParser::T__32);
        setState(373);
        antlrcpp::downCast<AndExpressionContext *>(_localctx)->right = comparisonExpression(); 
      }
      setState(378);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- OrExpressionContext ------------------------------------------------------------------

WoglacParser::OrExpressionContext::OrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ComparisonExpressionContext* WoglacParser::OrExpressionContext::comparisonExpression() {
  return getRuleContext<WoglacParser::ComparisonExpressionContext>(0);
}

WoglacParser::OrExpressionContext* WoglacParser::OrExpressionContext::orExpression() {
  return getRuleContext<WoglacParser::OrExpressionContext>(0);
}


size_t WoglacParser::OrExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleOrExpression;
}

void WoglacParser::OrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOrExpression(this);
}

void WoglacParser::OrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOrExpression(this);
}


WoglacParser::OrExpressionContext* WoglacParser::orExpression() {
   return orExpression(0);
}

WoglacParser::OrExpressionContext* WoglacParser::orExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  WoglacParser::OrExpressionContext *_localctx = _tracker.createInstance<OrExpressionContext>(_ctx, parentState);
  WoglacParser::OrExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, WoglacParser::RuleOrExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(380);
    antlrcpp::downCast<OrExpressionContext *>(_localctx)->base = comparisonExpression();
    _ctx->stop = _input->LT(-1);
    setState(387);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<OrExpressionContext>(parentContext, parentState);
        _localctx->left = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleOrExpression);
        setState(382);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(383);
        match(WoglacParser::T__33);
        setState(384);
        antlrcpp::downCast<OrExpressionContext *>(_localctx)->right = comparisonExpression(); 
      }
      setState(389);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ComparisonExpressionContext ------------------------------------------------------------------

WoglacParser::ComparisonExpressionContext::ComparisonExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::AddExpressionContext *> WoglacParser::ComparisonExpressionContext::addExpression() {
  return getRuleContexts<WoglacParser::AddExpressionContext>();
}

WoglacParser::AddExpressionContext* WoglacParser::ComparisonExpressionContext::addExpression(size_t i) {
  return getRuleContext<WoglacParser::AddExpressionContext>(i);
}

tree::TerminalNode* WoglacParser::ComparisonExpressionContext::ComparisonOp() {
  return getToken(WoglacParser::ComparisonOp, 0);
}


size_t WoglacParser::ComparisonExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleComparisonExpression;
}

void WoglacParser::ComparisonExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparisonExpression(this);
}

void WoglacParser::ComparisonExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparisonExpression(this);
}

WoglacParser::ComparisonExpressionContext* WoglacParser::comparisonExpression() {
  ComparisonExpressionContext *_localctx = _tracker.createInstance<ComparisonExpressionContext>(_ctx, getState());
  enterRule(_localctx, 58, WoglacParser::RuleComparisonExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(395);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(390);
      antlrcpp::downCast<ComparisonExpressionContext *>(_localctx)->base = addExpression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(391);
      antlrcpp::downCast<ComparisonExpressionContext *>(_localctx)->left = addExpression(0);
      setState(392);
      antlrcpp::downCast<ComparisonExpressionContext *>(_localctx)->op = match(WoglacParser::ComparisonOp);
      setState(393);
      antlrcpp::downCast<ComparisonExpressionContext *>(_localctx)->right = addExpression(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddExpressionContext ------------------------------------------------------------------

WoglacParser::AddExpressionContext::AddExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::MultExpressionContext* WoglacParser::AddExpressionContext::multExpression() {
  return getRuleContext<WoglacParser::MultExpressionContext>(0);
}

WoglacParser::AddExpressionContext* WoglacParser::AddExpressionContext::addExpression() {
  return getRuleContext<WoglacParser::AddExpressionContext>(0);
}


size_t WoglacParser::AddExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleAddExpression;
}

void WoglacParser::AddExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddExpression(this);
}

void WoglacParser::AddExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddExpression(this);
}


WoglacParser::AddExpressionContext* WoglacParser::addExpression() {
   return addExpression(0);
}

WoglacParser::AddExpressionContext* WoglacParser::addExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  WoglacParser::AddExpressionContext *_localctx = _tracker.createInstance<AddExpressionContext>(_ctx, parentState);
  WoglacParser::AddExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, WoglacParser::RuleAddExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(398);
    antlrcpp::downCast<AddExpressionContext *>(_localctx)->base = multExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(405);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<AddExpressionContext>(parentContext, parentState);
        _localctx->left = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleAddExpression);
        setState(400);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(401);
        antlrcpp::downCast<AddExpressionContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == WoglacParser::T__23

        || _la == WoglacParser::T__25)) {
          antlrcpp::downCast<AddExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(402);
        antlrcpp::downCast<AddExpressionContext *>(_localctx)->right = multExpression(0); 
      }
      setState(407);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- MultExpressionContext ------------------------------------------------------------------

WoglacParser::MultExpressionContext::MultExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::UnaryExpressionContext* WoglacParser::MultExpressionContext::unaryExpression() {
  return getRuleContext<WoglacParser::UnaryExpressionContext>(0);
}

WoglacParser::MultExpressionContext* WoglacParser::MultExpressionContext::multExpression() {
  return getRuleContext<WoglacParser::MultExpressionContext>(0);
}

tree::TerminalNode* WoglacParser::MultExpressionContext::MultOp() {
  return getToken(WoglacParser::MultOp, 0);
}


size_t WoglacParser::MultExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleMultExpression;
}

void WoglacParser::MultExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultExpression(this);
}

void WoglacParser::MultExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultExpression(this);
}


WoglacParser::MultExpressionContext* WoglacParser::multExpression() {
   return multExpression(0);
}

WoglacParser::MultExpressionContext* WoglacParser::multExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  WoglacParser::MultExpressionContext *_localctx = _tracker.createInstance<MultExpressionContext>(_ctx, parentState);
  WoglacParser::MultExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, WoglacParser::RuleMultExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(409);
    antlrcpp::downCast<MultExpressionContext *>(_localctx)->base = unaryExpression();
    _ctx->stop = _input->LT(-1);
    setState(416);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<MultExpressionContext>(parentContext, parentState);
        _localctx->left = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleMultExpression);
        setState(411);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(412);
        antlrcpp::downCast<MultExpressionContext *>(_localctx)->op = match(WoglacParser::MultOp);
        setState(413);
        antlrcpp::downCast<MultExpressionContext *>(_localctx)->right = unaryExpression(); 
      }
      setState(418);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- UnaryExpressionContext ------------------------------------------------------------------

WoglacParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::InlineFunctionCallExpressionContext* WoglacParser::UnaryExpressionContext::inlineFunctionCallExpression() {
  return getRuleContext<WoglacParser::InlineFunctionCallExpressionContext>(0);
}


size_t WoglacParser::UnaryExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleUnaryExpression;
}

void WoglacParser::UnaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpression(this);
}

void WoglacParser::UnaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpression(this);
}

WoglacParser::UnaryExpressionContext* WoglacParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 64, WoglacParser::RuleUnaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(424);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WoglacParser::T__4:
      case WoglacParser::T__21:
      case WoglacParser::T__27:
      case WoglacParser::T__35:
      case WoglacParser::BlockLiteral:
      case WoglacParser::BoolLiteral:
      case WoglacParser::StringLiteral:
      case WoglacParser::Identifier:
      case WoglacParser::NumericLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(419);
        antlrcpp::downCast<UnaryExpressionContext *>(_localctx)->base = inlineFunctionCallExpression(0);
        break;
      }

      case WoglacParser::T__23:
      case WoglacParser::T__25: {
        enterOuterAlt(_localctx, 2);
        setState(420);
        antlrcpp::downCast<UnaryExpressionContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == WoglacParser::T__23

        || _la == WoglacParser::T__25)) {
          antlrcpp::downCast<UnaryExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(421);
        antlrcpp::downCast<UnaryExpressionContext *>(_localctx)->arg = inlineFunctionCallExpression(0);
        break;
      }

      case WoglacParser::T__18: {
        enterOuterAlt(_localctx, 3);
        setState(422);
        antlrcpp::downCast<UnaryExpressionContext *>(_localctx)->op = match(WoglacParser::T__18);
        setState(423);
        antlrcpp::downCast<UnaryExpressionContext *>(_localctx)->arg = inlineFunctionCallExpression(0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InlineFunctionCallExpressionContext ------------------------------------------------------------------

WoglacParser::InlineFunctionCallExpressionContext::InlineFunctionCallExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::AtomicExpressionContext* WoglacParser::InlineFunctionCallExpressionContext::atomicExpression() {
  return getRuleContext<WoglacParser::AtomicExpressionContext>(0);
}

WoglacParser::InlineFunctionCallExpressionContext* WoglacParser::InlineFunctionCallExpressionContext::inlineFunctionCallExpression() {
  return getRuleContext<WoglacParser::InlineFunctionCallExpressionContext>(0);
}

tree::TerminalNode* WoglacParser::InlineFunctionCallExpressionContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}

WoglacParser::ArugmentListExpressionContext* WoglacParser::InlineFunctionCallExpressionContext::arugmentListExpression() {
  return getRuleContext<WoglacParser::ArugmentListExpressionContext>(0);
}


size_t WoglacParser::InlineFunctionCallExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleInlineFunctionCallExpression;
}

void WoglacParser::InlineFunctionCallExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInlineFunctionCallExpression(this);
}

void WoglacParser::InlineFunctionCallExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInlineFunctionCallExpression(this);
}


WoglacParser::InlineFunctionCallExpressionContext* WoglacParser::inlineFunctionCallExpression() {
   return inlineFunctionCallExpression(0);
}

WoglacParser::InlineFunctionCallExpressionContext* WoglacParser::inlineFunctionCallExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  WoglacParser::InlineFunctionCallExpressionContext *_localctx = _tracker.createInstance<InlineFunctionCallExpressionContext>(_ctx, parentState);
  WoglacParser::InlineFunctionCallExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 66;
  enterRecursionRule(_localctx, 66, WoglacParser::RuleInlineFunctionCallExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(427);
    antlrcpp::downCast<InlineFunctionCallExpressionContext *>(_localctx)->base = atomicExpression();
    _ctx->stop = _input->LT(-1);
    setState(435);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<InlineFunctionCallExpressionContext>(parentContext, parentState);
        _localctx->arg1 = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleInlineFunctionCallExpression);
        setState(429);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(430);
        match(WoglacParser::T__16);
        setState(431);
        antlrcpp::downCast<InlineFunctionCallExpressionContext *>(_localctx)->id = match(WoglacParser::Identifier);
        setState(432);
        antlrcpp::downCast<InlineFunctionCallExpressionContext *>(_localctx)->args = arugmentListExpression(); 
      }
      setState(437);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AtomicExpressionContext ------------------------------------------------------------------

WoglacParser::AtomicExpressionContext::AtomicExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::FunctionCallExpressionContext* WoglacParser::AtomicExpressionContext::functionCallExpression() {
  return getRuleContext<WoglacParser::FunctionCallExpressionContext>(0);
}

WoglacParser::LiteralExpressionContext* WoglacParser::AtomicExpressionContext::literalExpression() {
  return getRuleContext<WoglacParser::LiteralExpressionContext>(0);
}

WoglacParser::ParentExpressionContext* WoglacParser::AtomicExpressionContext::parentExpression() {
  return getRuleContext<WoglacParser::ParentExpressionContext>(0);
}

WoglacParser::BiomeParamExpressionContext* WoglacParser::AtomicExpressionContext::biomeParamExpression() {
  return getRuleContext<WoglacParser::BiomeParamExpressionContext>(0);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::AtomicExpressionContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}


size_t WoglacParser::AtomicExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleAtomicExpression;
}

void WoglacParser::AtomicExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtomicExpression(this);
}

void WoglacParser::AtomicExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtomicExpression(this);
}

WoglacParser::AtomicExpressionContext* WoglacParser::atomicExpression() {
  AtomicExpressionContext *_localctx = _tracker.createInstance<AtomicExpressionContext>(_ctx, getState());
  enterRule(_localctx, 68, WoglacParser::RuleAtomicExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(443);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(438);
      antlrcpp::downCast<AtomicExpressionContext *>(_localctx)->funcCall = functionCallExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(439);
      antlrcpp::downCast<AtomicExpressionContext *>(_localctx)->lit = literalExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(440);
      antlrcpp::downCast<AtomicExpressionContext *>(_localctx)->par = parentExpression();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(441);
      antlrcpp::downCast<AtomicExpressionContext *>(_localctx)->bio = biomeParamExpression();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(442);
      antlrcpp::downCast<AtomicExpressionContext *>(_localctx)->id = extendedIdentifier();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArugmentListExpressionContext ------------------------------------------------------------------

WoglacParser::ArugmentListExpressionContext::ArugmentListExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WoglacParser::ExpressionContext *> WoglacParser::ArugmentListExpressionContext::expression() {
  return getRuleContexts<WoglacParser::ExpressionContext>();
}

WoglacParser::ExpressionContext* WoglacParser::ArugmentListExpressionContext::expression(size_t i) {
  return getRuleContext<WoglacParser::ExpressionContext>(i);
}


size_t WoglacParser::ArugmentListExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleArugmentListExpression;
}

void WoglacParser::ArugmentListExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArugmentListExpression(this);
}

void WoglacParser::ArugmentListExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArugmentListExpression(this);
}

WoglacParser::ArugmentListExpressionContext* WoglacParser::arugmentListExpression() {
  ArugmentListExpressionContext *_localctx = _tracker.createInstance<ArugmentListExpressionContext>(_ctx, getState());
  enterRule(_localctx, 70, WoglacParser::RuleArugmentListExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(445);
    match(WoglacParser::T__21);
    setState(457);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WoglacParser::T__4)
      | (1ULL << WoglacParser::T__18)
      | (1ULL << WoglacParser::T__21)
      | (1ULL << WoglacParser::T__23)
      | (1ULL << WoglacParser::T__25)
      | (1ULL << WoglacParser::T__27)
      | (1ULL << WoglacParser::T__35)
      | (1ULL << WoglacParser::BlockLiteral)
      | (1ULL << WoglacParser::BoolLiteral)
      | (1ULL << WoglacParser::StringLiteral)
      | (1ULL << WoglacParser::Identifier)
      | (1ULL << WoglacParser::NumericLiteral))) != 0)) {
      setState(446);
      antlrcpp::downCast<ArugmentListExpressionContext *>(_localctx)->expressionContext = expression();
      antlrcpp::downCast<ArugmentListExpressionContext *>(_localctx)->args.push_back(antlrcpp::downCast<ArugmentListExpressionContext *>(_localctx)->expressionContext);
      setState(451);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(447);
          match(WoglacParser::T__31);
          setState(448);
          antlrcpp::downCast<ArugmentListExpressionContext *>(_localctx)->expressionContext = expression();
          antlrcpp::downCast<ArugmentListExpressionContext *>(_localctx)->args.push_back(antlrcpp::downCast<ArugmentListExpressionContext *>(_localctx)->expressionContext); 
        }
        setState(453);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx);
      }
      setState(455);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WoglacParser::T__31) {
        setState(454);
        match(WoglacParser::T__31);
      }
    }
    setState(459);
    match(WoglacParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BiomeParamExpressionContext ------------------------------------------------------------------

WoglacParser::BiomeParamExpressionContext::BiomeParamExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::BiomeParamExpressionContext::extendedIdentifier() {
  return getRuleContext<WoglacParser::ExtendedIdentifierContext>(0);
}

tree::TerminalNode* WoglacParser::BiomeParamExpressionContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}

std::vector<WoglacParser::ExpressionContext *> WoglacParser::BiomeParamExpressionContext::expression() {
  return getRuleContexts<WoglacParser::ExpressionContext>();
}

WoglacParser::ExpressionContext* WoglacParser::BiomeParamExpressionContext::expression(size_t i) {
  return getRuleContext<WoglacParser::ExpressionContext>(i);
}


size_t WoglacParser::BiomeParamExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleBiomeParamExpression;
}

void WoglacParser::BiomeParamExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBiomeParamExpression(this);
}

void WoglacParser::BiomeParamExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBiomeParamExpression(this);
}

WoglacParser::BiomeParamExpressionContext* WoglacParser::biomeParamExpression() {
  BiomeParamExpressionContext *_localctx = _tracker.createInstance<BiomeParamExpressionContext>(_ctx, getState());
  enterRule(_localctx, 72, WoglacParser::RuleBiomeParamExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(461);
    match(WoglacParser::T__4);
    setState(462);
    match(WoglacParser::T__21);
    setState(463);
    antlrcpp::downCast<BiomeParamExpressionContext *>(_localctx)->param = extendedIdentifier();
    setState(464);
    match(WoglacParser::T__31);
    setState(465);
    antlrcpp::downCast<BiomeParamExpressionContext *>(_localctx)->method = match(WoglacParser::Identifier);
    setState(470);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == WoglacParser::T__31) {
      setState(466);
      match(WoglacParser::T__31);
      setState(467);
      antlrcpp::downCast<BiomeParamExpressionContext *>(_localctx)->expressionContext = expression();
      antlrcpp::downCast<BiomeParamExpressionContext *>(_localctx)->params.push_back(antlrcpp::downCast<BiomeParamExpressionContext *>(_localctx)->expressionContext);
      setState(472);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(473);
    match(WoglacParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallExpressionContext ------------------------------------------------------------------

WoglacParser::FunctionCallExpressionContext::FunctionCallExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::FunctionCallExpressionContext::Identifier() {
  return getToken(WoglacParser::Identifier, 0);
}

WoglacParser::ArugmentListExpressionContext* WoglacParser::FunctionCallExpressionContext::arugmentListExpression() {
  return getRuleContext<WoglacParser::ArugmentListExpressionContext>(0);
}


size_t WoglacParser::FunctionCallExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleFunctionCallExpression;
}

void WoglacParser::FunctionCallExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallExpression(this);
}

void WoglacParser::FunctionCallExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallExpression(this);
}

WoglacParser::FunctionCallExpressionContext* WoglacParser::functionCallExpression() {
  FunctionCallExpressionContext *_localctx = _tracker.createInstance<FunctionCallExpressionContext>(_ctx, getState());
  enterRule(_localctx, 74, WoglacParser::RuleFunctionCallExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(475);
    antlrcpp::downCast<FunctionCallExpressionContext *>(_localctx)->id = match(WoglacParser::Identifier);
    setState(476);
    antlrcpp::downCast<FunctionCallExpressionContext *>(_localctx)->args = arugmentListExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExtendedIdentifierContext ------------------------------------------------------------------

WoglacParser::ExtendedIdentifierContext::ExtendedIdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> WoglacParser::ExtendedIdentifierContext::Identifier() {
  return getTokens(WoglacParser::Identifier);
}

tree::TerminalNode* WoglacParser::ExtendedIdentifierContext::Identifier(size_t i) {
  return getToken(WoglacParser::Identifier, i);
}


size_t WoglacParser::ExtendedIdentifierContext::getRuleIndex() const {
  return WoglacParser::RuleExtendedIdentifier;
}

void WoglacParser::ExtendedIdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExtendedIdentifier(this);
}

void WoglacParser::ExtendedIdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExtendedIdentifier(this);
}

WoglacParser::ExtendedIdentifierContext* WoglacParser::extendedIdentifier() {
  ExtendedIdentifierContext *_localctx = _tracker.createInstance<ExtendedIdentifierContext>(_ctx, getState());
  enterRule(_localctx, 76, WoglacParser::RuleExtendedIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(478);
    antlrcpp::downCast<ExtendedIdentifierContext *>(_localctx)->identifierToken = match(WoglacParser::Identifier);
    antlrcpp::downCast<ExtendedIdentifierContext *>(_localctx)->id.push_back(antlrcpp::downCast<ExtendedIdentifierContext *>(_localctx)->identifierToken);
    setState(483);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(479);
        match(WoglacParser::T__34);
        setState(480);
        antlrcpp::downCast<ExtendedIdentifierContext *>(_localctx)->identifierToken = match(WoglacParser::Identifier);
        antlrcpp::downCast<ExtendedIdentifierContext *>(_localctx)->id.push_back(antlrcpp::downCast<ExtendedIdentifierContext *>(_localctx)->identifierToken); 
      }
      setState(485);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralExpressionContext ------------------------------------------------------------------

WoglacParser::LiteralExpressionContext::LiteralExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WoglacParser::LiteralExpressionContext::NumericLiteral() {
  return getToken(WoglacParser::NumericLiteral, 0);
}

tree::TerminalNode* WoglacParser::LiteralExpressionContext::BlockLiteral() {
  return getToken(WoglacParser::BlockLiteral, 0);
}

tree::TerminalNode* WoglacParser::LiteralExpressionContext::BoolLiteral() {
  return getToken(WoglacParser::BoolLiteral, 0);
}

tree::TerminalNode* WoglacParser::LiteralExpressionContext::StringLiteral() {
  return getToken(WoglacParser::StringLiteral, 0);
}


size_t WoglacParser::LiteralExpressionContext::getRuleIndex() const {
  return WoglacParser::RuleLiteralExpression;
}

void WoglacParser::LiteralExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteralExpression(this);
}

void WoglacParser::LiteralExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WoglacListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteralExpression(this);
}

WoglacParser::LiteralExpressionContext* WoglacParser::literalExpression() {
  LiteralExpressionContext *_localctx = _tracker.createInstance<LiteralExpressionContext>(_ctx, getState());
  enterRule(_localctx, 78, WoglacParser::RuleLiteralExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(493);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WoglacParser::T__27:
      case WoglacParser::T__35:
      case WoglacParser::NumericLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(487);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == WoglacParser::T__27

        || _la == WoglacParser::T__35) {
          setState(486);
          _la = _input->LA(1);
          if (!(_la == WoglacParser::T__27

          || _la == WoglacParser::T__35)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
        }
        setState(489);
        antlrcpp::downCast<LiteralExpressionContext *>(_localctx)->num = match(WoglacParser::NumericLiteral);
        break;
      }

      case WoglacParser::BlockLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(490);
        antlrcpp::downCast<LiteralExpressionContext *>(_localctx)->block = match(WoglacParser::BlockLiteral);
        break;
      }

      case WoglacParser::BoolLiteral: {
        enterOuterAlt(_localctx, 3);
        setState(491);
        antlrcpp::downCast<LiteralExpressionContext *>(_localctx)->bool_ = match(WoglacParser::BoolLiteral);
        break;
      }

      case WoglacParser::StringLiteral: {
        enterOuterAlt(_localctx, 4);
        setState(492);
        antlrcpp::downCast<LiteralExpressionContext *>(_localctx)->string = match(WoglacParser::StringLiteral);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool WoglacParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 27: return andExpressionSempred(antlrcpp::downCast<AndExpressionContext *>(context), predicateIndex);
    case 28: return orExpressionSempred(antlrcpp::downCast<OrExpressionContext *>(context), predicateIndex);
    case 30: return addExpressionSempred(antlrcpp::downCast<AddExpressionContext *>(context), predicateIndex);
    case 31: return multExpressionSempred(antlrcpp::downCast<MultExpressionContext *>(context), predicateIndex);
    case 33: return inlineFunctionCallExpressionSempred(antlrcpp::downCast<InlineFunctionCallExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool WoglacParser::andExpressionSempred(AndExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool WoglacParser::orExpressionSempred(OrExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool WoglacParser::addExpressionSempred(AddExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool WoglacParser::multExpressionSempred(MultExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool WoglacParser::inlineFunctionCallExpressionSempred(InlineFunctionCallExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void WoglacParser::initialize() {
  std::call_once(woglacParserOnceFlag, woglacParserInitialize);
}
