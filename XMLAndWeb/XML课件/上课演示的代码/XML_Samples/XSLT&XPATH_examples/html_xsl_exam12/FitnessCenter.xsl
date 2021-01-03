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
                Member's Phone Numbers:
                <TABLE border="1" width="25%">
                    <TR><TH>Name</TH><TH>Type</TH><TH>Number</TH></TR>
                    <xsl:for-each select="/FitnessCenter/Member">
                        <xsl:variable name="name" select="Name"/>
                        <xsl:for-each select="Phone">
                            <TR>
                                <TD><xsl:value-of select="$name"/></TD>
                                <TD><xsl:value-of select="@type"/></TD>
                                <TD><xsl:value-of select="."/></TD>
                            </TR>
                        </xsl:for-each>
                    </xsl:for-each>
                </TABLE>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>