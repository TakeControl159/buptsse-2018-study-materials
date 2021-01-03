<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Fitness Center</TITLE>
            </HEAD>
            <BODY>
                <xsl:for-each select="/FitnessCenter/Member">
                    Member <xsl:number value="position()" format="1"/> Attributes:
                    <BR/>
                    <xsl:for-each select="@*">
                        Currently processing the Member attribute:
                           <xsl:value-of select="name(.)"/>
                           <BR/>
                        Its value is:
                           <xsl:value-of select="."/>
                           <BR/>
                    </xsl:for-each>
                    Member <xsl:number value="position()" format="1"/> Elements:
                    <BR/>
                    <xsl:for-each select="*">
                        Currently processing the Member element:
                           <xsl:value-of select="name(.)"/>
                           <BR/>
                        Its value is:
                           <xsl:value-of select="."/>
                           <BR/>
                    </xsl:for-each>
                </xsl:for-each>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>