
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_xml_pipeline_ValidationConsumer$EmptyRecognizer__
#define __gnu_xml_pipeline_ValidationConsumer$EmptyRecognizer__

#pragma interface

#include <gnu/xml/pipeline/ValidationConsumer$Recognizer.h>
extern "Java"
{
  namespace gnu
  {
    namespace xml
    {
      namespace pipeline
      {
          class ValidationConsumer$ElementInfo;
          class ValidationConsumer$EmptyRecognizer;
          class ValidationConsumer$Recognizer;
      }
    }
  }
}

class gnu::xml::pipeline::ValidationConsumer$EmptyRecognizer : public ::gnu::xml::pipeline::ValidationConsumer$Recognizer
{

public:
  ValidationConsumer$EmptyRecognizer(::gnu::xml::pipeline::ValidationConsumer$ElementInfo *);
public: // actually package-private
  jboolean acceptCharacters();
  ::gnu::xml::pipeline::ValidationConsumer$Recognizer * acceptElement(::java::lang::String *);
public:
  static ::java::lang::Class class$;
};

#endif // __gnu_xml_pipeline_ValidationConsumer$EmptyRecognizer__
