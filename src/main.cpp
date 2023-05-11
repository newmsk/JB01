#include<pybind11/pybind11.h>

typedef unsigned char UCHAR;
typedef unsigned long ULONG;
typedef unsigned int  UINT;
typedef unsigned short USHORT;

#include"lib/JB01_Compress.h"
#include"lib/JB01_Decompress.h"

#define COMPRESSED_HEADER_SIZE 9

namespace py = pybind11;

namespace JB01LZSS {
	py::bytes Compress(py::bytes input, int level = 4)
	{
		JB01_Compress c{};
		char* bBuf = nullptr; py::ssize_t size = 0;
		PYBIND11_BYTES_AS_STRING_AND_SIZE(input.ptr(), &bBuf, &size);
		c.SetInputType(HS_COMP_MEM);
		c.SetOutputType(HS_COMP_MEM);
		c.SetInputBuffer(reinterpret_cast<UCHAR*>(bBuf), static_cast<ULONG>(size));
		auto output = std::make_unique<char[]>(size + COMPRESSED_HEADER_SIZE);
		c.SetOutputBuffer(reinterpret_cast<UCHAR*>(output.get()));
		c.SetCompressionLevel(level);
		int nRes = c.Compress();
		int compressed_size = c.GetCompressedSize();
		if (nRes != JB01_E_OK || !compressed_size)
			return py::bytes{};
		return py::bytes(output.get(), compressed_size);
	}

	py::bytes Decompress(py::bytes input)
	{
		JB01_Decompress d{};
		char* bBuf = nullptr; py::ssize_t size = 0;
		PYBIND11_BYTES_AS_STRING_AND_SIZE(input.ptr(), &bBuf, &size);
		d.SetInputType(HS_COMP_MEM);
		d.SetOutputType(HS_COMP_MEM);
		d.SetInputBuffer(reinterpret_cast<UCHAR*>(bBuf));
		int decompressed_size = d.GetDecompressedSize();
		if (!decompressed_size)
			return py::bytes{};
		auto output = std::make_unique<char[]>(decompressed_size);
		d.SetOutputBuffer(reinterpret_cast<UCHAR*>(output.get()));
		int nRes = d.Decompress();
		if (nRes != JB01_E_OK)
			return py::bytes{};
		return py::bytes(output.get(), decompressed_size);
	}
};


PYBIND11_MODULE(jb01, m) {
	m.doc() = "Python module to wrap JB01 LZSS compression algorithm.";

	m.def("compress", & JB01LZSS::Compress, py::arg("input"), py::arg("level") = 4);
	m.def("decompress", & JB01LZSS::Decompress, py::arg("input"));
}
