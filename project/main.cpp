#include <iostream>
#include <clang-c/Index.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

void getFieldDecls(CXCursor node, vector<CXCursor> *fieldDecls) {
    fieldDecls->clear();

    clang_visitChildren
    (node,
     [](CXCursor cursor, CXCursor parent, CXClientData decls) {
        if (clang_getCursorKind(cursor) == CXCursorKind::CXCursor_FieldDecl) {
            static_cast<vector<CXCursor>*>(decls)->push_back(cursor);
        }

         return CXChildVisit_Continue;
    }, fieldDecls);
}

void printNode(CXCursor node, CXTranslationUnit unit, CXToken *tokensBuffer) {
    CXSourceRange range = clang_getCursorExtent(node);
    unsigned int tokensNum;
    clang_tokenize(unit, range, &tokensBuffer, &tokensNum);

    for (int i = 0; i < tokensNum; i++) {
        CXString spelling = clang_getTokenSpelling(unit, tokensBuffer[i]);
        cout << clang_getCString(spelling) << " | ";
        clang_disposeString(spelling);
    }
    cout << endl;
}

void printStructAndFields(CXCursor structDecl, CXTranslationUnit unit,
                          vector<CXCursor> *fieldDecls, CXToken *tokensBuffer) {
    cout << "Struct decl: ";
    printNode(structDecl, unit, tokensBuffer);

    for (CXCursor filed : *fieldDecls) {
        cout << "Field decl: ";
        printNode(filed, unit, tokensBuffer);
    }
}



void traverseAST(CXTranslationUnit unit, CXCursor node) {
    vector<CXCursor> fieldDecls;
    fieldDecls.reserve(100);

    struct MyData {
        vector<CXCursor> *decls;
        CXTranslationUnit tu;
        CXToken *tokensBuffer;

        MyData(int n = 100) {
            tokensBuffer = new CXToken[n];
        }
        ~MyData() {
            delete[] tokensBuffer;
        }
    } clientData;
    clientData.tu = unit;
    clientData.decls = &fieldDecls;

    clang_visitChildren
    (node,
     [](CXCursor cursor, CXCursor parent, CXClientData clientData) {
        CXTranslationUnit unit = static_cast<MyData*>(clientData)->tu;
        vector<CXCursor> *fieldDecls = static_cast<MyData*>(clientData)->decls;
        CXToken *buffer = static_cast<MyData*>(clientData)->tokensBuffer;

        if (clang_getCursorKind(cursor) == CXCursorKind::CXCursor_StructDecl) {
            getFieldDecls(cursor, fieldDecls);
            printStructAndFields(cursor, unit, fieldDecls, buffer);
        }
         return CXChildVisit_Recurse;
    }, &clientData);
}

int main() {

    //cout << sizeof (CXCursor) << endl;

    CXIndex index = clang_createIndex(false, false);
    CXTranslationUnit unit = clang_parseTranslationUnit (
            index,                           // CIdx
            "/home/dszhdankin/CLionProjects/practice_huawei/project/code_examples/example.cpp",  // source_filename
            nullptr ,                        // command_line_args
            0 ,                        // num_command_line_args
            nullptr,                                // unsave_files
            0,                                // num_unsaved_files
            CXTranslationUnit_None           // options
            );

    if (unit != nullptr)
        cout << "Unit created" << endl;
    else
        cout << "Unit not created" << endl;

    CXCursor root = clang_getTranslationUnitCursor(unit);
    string offset;

    traverseAST(unit, root);


    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);

    return 0;
}
