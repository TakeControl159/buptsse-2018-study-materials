<results>
  {
for $b in doc("books.xml")/bib/book
where some $ba in $b/author satisfies
        ($ba/last:=$l and $ba/first:=$f)
order by $b/title
return $b/title
}
</results>

(: Stylus Studio meta-information - (c) 2004-2005. Progress Software Corporation. All rights reserved.
<metaInformation>
<scenarios ><scenario default="yes" name="Scenario1" userelativepaths="yes" externalpreview="no" url="" outputurl="" processortype="internal" tcpport="2233" profilemode="0" profiledepth="" profilelength="" urlprofilexml="" commandline="" additionalpath="" additionalclasspath="" postprocessortype="none" postprocesscommandline="" postprocessadditionalpath="" postprocessgeneratedext="" host="" port="8000" user="" password=""/></scenarios><MapperMetaTag><MapperInfo srcSchemaPathIsRelative="yes" srcSchemaInterpretAsXML="no" destSchemaPath="" destSchemaRoot="" destSchemaPathIsRelative="yes" destSchemaInterpretAsXML="no"/><MapperBlockPosition><template name="xquery_body"></template></MapperBlockPosition></MapperMetaTag>
</metaInformation>
:)