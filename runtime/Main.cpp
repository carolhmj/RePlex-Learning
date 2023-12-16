#include <gtest/gtest.h>
#include <RePlex.h>
#include <cstdlib>
#include <fstream>
#include <Test.h>

const char* g_Test_v1 = 
"#include \"pub/Test.h\"\n"
"int bar = 3;\n"
"int foo(int x)\n"
"{\n"
"  return x + 5;\n"
"}";

const char* g_Test_v2 = 
"#include \"pub/Test.h\"\n"
"int bar = -2;\n"
"int foo(int x)\n"
"{\n"
"  return x - 5;\n"
"}";

class RePlexTest : public ::testing::Test {
public:
	virtual void SetUp() {
		MyWriteFile("test/Test.cpp", g_Test_v1);
		Compile(1);
		TestModule::LoadMyLibrary();
	}

	void ChangeAndReload() {
		MyWriteFile("test/Test.cpp", g_Test_v2);
		Compile(2);
		TestModule::ReloadLibrary();
	}

	virtual void TearDown() {
		// this method wasnt defined!
		//TestModule::UnloadLibrary();
		MyWriteFile("test/Test.cpp", g_Test_v1);
		Compile(1);
	}

private:
	void MyWriteFile(const char* path, const char* test) {
		std::ofstream out(path, std::ios_base::trunc | std::ios_base::out);
	}

	void Compile(int version) {
		if (version == m_version) {
			return;
		}

		m_version = version;
		EXPECT_EQ(std::system("make"), 0);

		Sleep(1);
	}

	int m_version = 1;
};

TEST_F(RePlexTest, VariableReload) {
	EXPECT_EQ(TestModule::GetBar(), 3);
	ChangeAndReload();
	EXPECT_EQ(TestModule::GetBar(), -2);
}

TEST_F(RePlexTest, FunctionReload) {
	EXPECT_EQ(TestModule::Foo(4), 9);
	ChangeAndReload();
	EXPECT_EQ(TestModule::Foo(4), -1);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}