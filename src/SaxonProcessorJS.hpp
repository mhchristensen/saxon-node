#pragma once
#include <map>

#include <v8.h>
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include <string>
#include <cstring>
#include <memory>

#include "SaxonProcessor.h"

namespace saxon_node {

    using namespace v8;
    //using namespace node;

    class XsltProcessorJS;
    class XQueryProcessorJS;

    class SaxonProcessorJS : public node::ObjectWrap {
        friend class XsltProcessorJS;
        friend class XQueryProcessorJS;
    protected:
        std::string cwd;
        std::shared_ptr<SaxonProcessor> processor;
    public:

        static void Initialize(Handle<Object> target) {
            // instantiate constructor function template
            Local<FunctionTemplate> t = FunctionTemplate::New(v8::Isolate::GetCurrent(), New);
            t->SetClassName(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SaxonProcessor"));
            t->InstanceTemplate()->SetInternalFieldCount(1);
            Constructor.Reset(v8::Isolate::GetCurrent(), t);
            // member method prototypes
            NODE_SET_PROTOTYPE_METHOD(t, "newTransformer", newTransformer);
            NODE_SET_PROTOTYPE_METHOD(t, "newXQueryProcessor", newXQueryProcessor);
            NODE_SET_PROTOTYPE_METHOD(t, "parseFile", parseFile);
            NODE_SET_PROTOTYPE_METHOD(t, "parseURI", parseURI);
            NODE_SET_PROTOTYPE_METHOD(t, "setSourceValue", setSourceValue);
            NODE_SET_PROTOTYPE_METHOD(t, "setSourceFile", setSourceFile);
            NODE_SET_PROTOTYPE_METHOD(t, "setProperty", setProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "getProperties", getProperties);
            NODE_SET_PROTOTYPE_METHOD(t, "setcwd", setcwd);
            NODE_SET_PROTOTYPE_METHOD(t, "setResourcesDirectory", setResourcesDirectory);
            NODE_SET_PROTOTYPE_METHOD(t, "version", version);
            //        Local<Function> f=t->GetFunction();
            // append this function to the target object
            target->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SaxonProcessor"), t->GetFunction());
        };


    private:

        SaxonProcessorJS() : SaxonProcessorJS(false) {

        };

        SaxonProcessorJS(bool l) : cwd(""), processor (new SaxonProcessor(false)) {
//            processor.reset(new SaxonProcessor(false));
        };
        SaxonProcessorJS(const SaxonProcessorJS& orig) = delete;

        ~SaxonProcessorJS() {
        };
        static Persistent<FunctionTemplate> Constructor;

        static void New(const v8::FunctionCallbackInfo<Value>& args) {
            // create processor object
            SaxonProcessorJS* sp;
            if (args.Length() < 1)
            {
                sp = new SaxonProcessorJS();
            }
            else
            {
                sp = new SaxonProcessorJS(args[0]->ToBoolean()->BooleanValue());
            }
//            std::cout<<"xsl:product-name "<<sp->processor->getProperty("xsl:product-name")<<std::endl;

            // extend target object with file
            sp->Wrap(args.This());

            // attach various properties
            //args.This()->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "path"), String::NewFromUtf8(v8::Isolate::GetCurrent(), f->m_file->getFileName().c_str()));
        };
        static void newTransformer(const v8::FunctionCallbackInfo<Value>& args);

        static void newXQueryProcessor(const v8::FunctionCallbackInfo<Value>& args);

        static void parseFile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void parseURI(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setSourceValue(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setSourceFile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setProperty(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void getProperties(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setcwd(const v8::FunctionCallbackInfo<Value>& args) {
            if(args.Length()==1 && args[0]->IsString())
            {
                SaxonProcessorJS* sp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());
                String::Utf8Value cwd(args[0]->ToString());
                sp->processor->setcwd((*cwd));
                args.GetReturnValue().SetUndefined();
            }
        };

        static void setResourcesDirectory(const v8::FunctionCallbackInfo<Value>& args) {
            if(args.Length()==1 && args[0]->IsString())
            {
                SaxonProcessorJS* sp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());
                String::Utf8Value resourcesDirectory(args[0]->ToString());
                sp->processor->setResourcesDirectory((*resourcesDirectory));
                args.GetReturnValue().SetUndefined();
            }
        };

        static void version(const v8::FunctionCallbackInfo<Value>& args) {
                SaxonProcessorJS* sp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());
                const char* buffer=sp->processor->version();
                args.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), buffer, String::kNormalString, std::strlen(buffer)));
        };

    protected:

    };

};

