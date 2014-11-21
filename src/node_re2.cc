#include <node.h>
#include <nan.h>
#include <re2/re2.h>
#include "./node_re2.h"

using v8::String;
using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::Persistent;
using v8::Local;

static Persistent<FunctionTemplate> constructor;

RE2Wrap::RE2Wrap(std::string& regexp, const RE2::Options& options)
{
    this->m_Source = regexp;
    this->m_RE2 = new RE2(regexp, options);
}

RE2Wrap::~RE2Wrap()
{
    delete this->m_RE2;
}

/*
 * RE2 constructor
 */
NAN_METHOD(RE2Wrap::New)
{
    NanScope();
    if (args.Length() == 0)
    {
        return NanThrowError("Missing parameter regexp");
    }

    if (!args[0]->IsString())
    {
        return NanThrowTypeError("Parameter regexp must be a string");
    }

    /* TODO allow JS to pass in options */
    RE2::Options options;
    /* Don't log errors to the console from C++-land,
     * instead it will be thrown as a JS Error below
     */
    options.set_log_errors(false);
    std::string regexp(*String::Utf8Value(args[0]->ToString()));
    RE2Wrap *wrap = new RE2Wrap(regexp, options);
    wrap->Wrap(args.This());

    if (!wrap->m_RE2->ok())
    {
        return NanThrowError(NanNew<String>(wrap->m_RE2->error()));
    }

    NanReturnThis();
}

/*
 * RE2.replace()
 */
NAN_METHOD(RE2Wrap::Replace)
{
    NanScope();
    if (args.Length() != 2)
    {
        return NanThrowError("replace() expects 2 parameters (string, replacement)");
    }

    if (!args[0]->IsString() || !args[1]->IsString())
    {
        return NanThrowTypeError("Both parameters must be strings");
    }

    RE2Wrap *wrap = ObjectWrap::Unwrap<RE2Wrap>(args.This());
    std::string input(*String::Utf8Value(args[0]->ToString()));

    RE2::Replace(&input, *wrap->m_RE2, *String::Utf8Value(args[1]->ToString()));

    NanReturnValue(NanNew<String>(input));
}

/*
 * RE2.replaceAll()
 */
NAN_METHOD(RE2Wrap::ReplaceAll)
{
    NanScope();
    if (args.Length() != 2)
    {
        return NanThrowError("replaceAll() expects 2 parameters (string, replacement)");
    }

    if (!args[0]->IsString() || !args[1]->IsString())
    {
        return NanThrowTypeError("Both parameters must be strings");
    }

    RE2Wrap *wrap = ObjectWrap::Unwrap<RE2Wrap>(args.This());
    std::string input(*String::Utf8Value(args[0]->ToString()));

    RE2::GlobalReplace(&input, *wrap->m_RE2, *String::Utf8Value(args[1]->ToString()));

    NanReturnValue(NanNew<String>(input));
}

/*
 * Property RE2.source
 */
NAN_GETTER(RE2Wrap::GetSource)
{
    NanScope();
    RE2Wrap *wrap = ObjectWrap::Unwrap<RE2Wrap>(args.This());
    NanReturnValue(NanNew<String>(wrap->m_Source));
}

/*
 * Class initializer.
 * This stuff is not done directly in the main Init() below
 * because it references private methods of the RE2Wrap class
 */
void RE2Wrap::Init()
{
    Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(RE2Wrap::New);
    NanAssignPersistent(constructor, tpl);
    tpl->SetClassName(NanNew<String>("RE2"));
    tpl->InstanceTemplate()->SetInternalFieldCount(2); // m_RE2, m_Source

    /* instance methods */
    tpl->InstanceTemplate()->Set(NanNew<String>("replace"),
        FunctionTemplate::New(RE2Wrap::Replace)->GetFunction());
    tpl->InstanceTemplate()->Set(NanNew<String>("replaceAll"),
        FunctionTemplate::New(RE2Wrap::ReplaceAll)->GetFunction());

    /* instance properties */
    tpl->InstanceTemplate()->SetAccessor(NanNew<String>("source"), RE2Wrap::GetSource);
}

void Init(Handle<Object> exports, Handle<Object> module)
{
    RE2Wrap::Init();
    Local<FunctionTemplate> constructorHandle = NanNew(constructor);

    module->Set(NanNew<String>("exports"), constructorHandle->GetFunction());
}

NODE_MODULE(re2, Init);
