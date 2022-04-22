#include "wga_structureoutputdata_cpu.h"


WGA_StructureOutputData_CPU::SubChunkRecord::SubChunkRecord() {

}

bool WGA_StructureOutputData_CPU::SubChunkRecord::shouldUseFlat(int addedRecordCount) {
	/// When block count <= associativeDataLimit, associativeData is used, otherwise flatData for sunChunkSize is used
	static constexpr int associativeDataLimit = 512;

	if(!flatData.empty())
		return true;

	if(associativeData.size() + addedRecordCount > associativeDataLimit) {
		flatData.resize(chunkVolume, blockID_undefined);

		auto resh = flatData.data();
		for(const auto &v : associativeData) {
			ASSERT(v.first < flatData.size());
			resh[v.first] = v.second;
		}

		associativeData.clear();
		return true;
	}

	return false;
}
