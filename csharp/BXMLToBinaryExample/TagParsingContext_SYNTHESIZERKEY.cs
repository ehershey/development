﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_SYNTHESIZERKEY    : TagParsingContext
    {
        private bool m_emitted = false;
        private byte m_val = 0;
        private bool val_parsed = false;

        public TagParsingContext_SYNTHESIZERKEY(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
            string[] taglist = {TagNames.SYNTHESIZERCODE};
            foreach (string tag in taglist)
            {
                Legaltags.Add(tag,tag);
            }
        }
        public override void parseValue(string val)
        {
            val_parsed = true;
            m_val = parseByte(val);
        }
        public override bool isTag(string tag)
        {
            return tag.ToLower().Equals(TagNames.SYNTHESIZERKEY);
        }
        public override string tagName()
        {
            return TagNames.SYNTHESIZERKEY;
        }
        public override void emit()
        {
            if( ! m_emitted)
            {
                if(! val_parsed)
                {
                    Console.Write("Line:"); 
                    base.OnLinenumber();
                    Console.WriteLine();
                    Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.SYNTHESIZERKEY.ToUpper()));
                    throw new MissingParameter();
                }
                else
                {
#if TRACE_EMIT            
                    Console.WriteLine(String.Format("::{0}::[{1}]",TagNames.SYNTHESIZERKEY.ToUpper(),m_val));
#endif
                    FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.SYNTHESIZERKEY]);
                    FileContext.Bw.Write((byte) 1);
                    FileContext.Bw.Write((byte) m_val);
                    m_emitted = true;
                }
            }
        }
        public override bool closeElementAction()
        {
            if(! val_parsed)
            {
                Console.Write("Line:"); 
                base.OnLinenumber();
                Console.WriteLine();
                Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.SYNTHESIZERKEY.ToUpper()));
            }
            else
            {
                emit();
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::/{0}::",TagNames.SYNTHESIZERKEY.ToUpper()));
#endif
                FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.SYNTHESIZERKEY] | END_TAG_FLAG));
            }
            return val_parsed;
        }

        public override void setOutputName(TagParsingDirector director)
        {
        }
    }
}