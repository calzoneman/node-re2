#ifndef _NODE_RE2_H
#define _NODE_RE2_H

#include <node.h>
#include <nan.h>
#include <re2/re2.h>

class RE2Wrap : public node::ObjectWrap {
    public:
        static void Init();

    private:
        explicit RE2Wrap(std::string& regexp, const RE2::Options& options);
        ~RE2Wrap();

        static NAN_METHOD(New);
        static NAN_METHOD(Replace);
        static NAN_METHOD(ReplaceAll);

        static NAN_GETTER(GetSource);

        RE2 *m_RE2;
        std::string m_Source;
};

#endif
