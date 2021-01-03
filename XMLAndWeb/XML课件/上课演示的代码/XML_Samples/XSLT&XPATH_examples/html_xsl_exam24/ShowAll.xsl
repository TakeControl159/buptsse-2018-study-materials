<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Members</TITLE>
            </HEAD>
            <BODY>
                <H1>Fitness Center Members (sorted alphabetically)</H1>
                <TABLE border="1">
                    <TR>
                        <TH>Name</TH>
                        <TH>Membership Level</TH>
                        <TH>Home Phone</TH>
                        <TH>Work Phone</TH>
                        <TH>Favorite Color</TH>
                    </TR>
                    <xsl:for-each select="/FitnessCenter/Member">
                        <xsl:sort select="Name" order="ascending"/>
                        <TR>
                             <TD><xsl:value-of select="Name"/></TD>
                             <TD><xsl:value-of select="@level"/></TD>
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