<Q7 xmlns:xlink="http://www.w3.org/1999/xlink">
{
for $a in (doc("bib.xml")/bib/book[publisher="Morgan Kaufmann Publishers"]/author)
    return <result>
    $a,
    for $t in /bib/book[author=$a]/title
    return $t
</result>
}
</Q7>
(: Stylus Studio meta-information - (c) 2004-2005. Progress Software Corporation. All rights reserved.
<metaInformation>
<scenarios ><scenario default="yes" name="Scenario1" userelativepaths="yes" externalpreview="no" url="" outputurl="" processortype="internal" tcpport="2233" profilemode="0" profiledepth="" profilelength="" urlprofilexml="" commandline="" additionalpath="" additionalclasspath="" postprocessortype="none" postprocesscommandline="" postprocessadditionalpath="" postprocessgeneratedext="" host="" port="8000" user="" password=""/></scenarios><MapperMetaTag><MapperInfo srcSchemaPathIsRelative="yes" srcSchemaInterpretAsXML="no" destSchemaPath="" destSchemaRoot="" destSchemaPathIsRelative="yes" destSchemaInterpretAsXML="no"/><MapperBlockPosition></MapperBlockPosition></MapperMetaTag>
</metaInformation>
:)