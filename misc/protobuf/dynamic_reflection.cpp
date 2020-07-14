/*
 * 测试protocol buffer 的动态反射  不需要每次编译bin，就能通过data和proto解析出新的结构，
 * 不过这种方式比静态解析 速度会慢 很多，有人测试是100倍左右
 * build by 
 * g++ dynamic_reflection.cpp -std=c++11 -lpthread -I ../../../install/protobuf/include/ -L ../../../install/protobuf/lib/  ../../../install/protobuf/lib/libprotobuf.a 
*/

//相对路径
#include "../../../install/protobuf/include/google/protobuf/dynamic_message.h"
#include "../../../install/protobuf/include/google/protobuf/compiler/importer.h"


#include <iostream>

using namespace std;
using namespace google::protobuf;
        
    // class DiskSourceTree;
    // class Importer;
    // class DynamicMessageFactory;
    // class Message;

int main() {
    compiler::DiskSourceTree  source_tree;
    source_tree.MapPath("", "./");

    // compiler::Importer importer(source_tree, NULL);
    compiler::Importer importer(&source_tree, nullptr);
    importer.Import("test.proto"); // runtime compile test.proto

    // descriptor
    const Descriptor *descriptor = importer.pool()->FindMessageTypeByName("SearchRequest");

    // build a dynamic message by "test.proto"
    DynamicMessageFactory factory;
    const Message *template_proto = factory.GetPrototype(descriptor);

    //create a real instance of "SearchRequest"
    Message *sr = template_proto->New();
    const Reflection *reflection = sr->GetReflection();
    const FieldDescriptor *field = NULL;

    // write the "SearchRequest" instance by reflection
    field = descriptor->FindFieldByName("query");
    reflection->SetString(sr, field, "reflection query field");
    field = descriptor->FindFieldByName("page_number");
    reflection->SetInt32(sr, field, 1);
    field = descriptor->FindFieldByName("result_per_page");
    reflection->SetInt32(sr, field, 2);

    //new
    field = descriptor->FindFieldByName("new_add_1");
    if (!field) {
        cout << "new_add_1 find failed ." << endl;
    } else {
        cout << "new_add_1 find success ." << endl;
        //check type skip
        //set
        reflection->SetInt32(sr, field, 3);
    }

    cout << sr->ShortDebugString() << endl;

    delete sr;

    return 0;
}
