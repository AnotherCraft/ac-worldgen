#pragma once

#include <vector>
#include <unordered_map>

#include "wga_datarecord_cpu.h"

class WGA_StructureOutputData_CPU {

public:
	struct SubChunkRecord {
		SubChunkRecord();

		std::vector<BlockID> flatData;
		std::vector<std::pair<uint16_t, BlockID>> associativeData;

		/// To be used when adding data. Returns if the program should use flat or associative data, when expecting addedRecordCount to be added
		bool shouldUseFlat(int addedRecordCount);
	};

public:
	std::unordered_map<BlockWorldPos, SubChunkRecord> subChunkRecords;
	int dataSize = 0;

};

using WGA_StructureOutputData_CPUPtr = std::shared_ptr<WGA_StructureOutputData_CPU>;


class WGA_StructureOutputDataRecord_CPU : public WGA_DataRecord_CPU {

public:
	std::vector<WGA_StructureOutputData_CPUPtr> data;
	int dataSizeV = 0;

public:
	virtual int dataSize() const override {
		return dataSizeV;
	};


};
