<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Welcome</TITLE>
            </HEAD>
            <BODY bgcolor="{FitnessCenter/Member/FavoriteColor}">
                Welcome <xsl:value-of select="/FitnessCenter/Member/Name"/>!
                <BR/>
                <xsl:if test="/FitnessCenter/Member/@level='platinum'">
                    Our special offer to platinum members today is ...
                    <BR/>
                </xsl:if>
                Your phone numbers are:
                <TABLE border="1" width="25%">
                    <TR><TH>Name</TH><TH>Type</TH><TH>Number</TH></TR>
                    <xsl:for-each select="/FitnessCenter/Member/Phone">
                        <TR>
                            <TD><xsl:value-of select="../Name"/></TD>
                            <TD><xsl:value-of select="@type"/></TD>
                            <TD><xsl:value-of select="."/></TD>
                        </TR>
                    </xsl:for-each>
                </TABLE>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>