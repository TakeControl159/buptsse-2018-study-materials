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
                <TABLE border="1" width="75%">
                    <TR><TH>Name</TH><TH>Phone(home)</TH><TH>Phone(work)</TH><TH>Favorite Color</TH></TR>
                    <xsl:for-each select="/FitnessCenter/Member">
                        <TR>
                            <TD><xsl:value-of select="Name"/></TD>
                            <TD><xsl:value-of select="Phone[@type='home']"/></TD>
                            <TD><xsl:value-of select="Phone[@type='work']"/></TD>
                            <TD><xsl:value-of select="FavoriteColor"/></TD>
                        </TR>
                    </xsl:for-each>
                    <xsl:variable name="fitnessCenter2" select="document('file://localhost/xml-course/xsl/examples/html-example20/FitnessCenter2.xml')"/>
                    <xsl:for-each select="$fitnessCenter2/FitnessCenter/Member">
                        <TR>
                            <TD><xsl:value-of select="Name"/></TD>
                            <TD><xsl:value-of select="Phone[@type='home']"/></TD>
                            <TD><xsl:value-of select="Phone[@type='work']"/></TD>
                            <TD><xsl:value-of select="FavoriteColor"/></TD>
                        </TR>
                    </xsl:for-each>
                </TABLE>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>