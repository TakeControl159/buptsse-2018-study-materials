<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Hyperlinked Juicer Name/Cost and Name/Description Tables</TITLE>
            </HEAD>
            <BODY>
                <TABLE BORDER="1" WIDTH="50%">
                    <TR>
                        <TH>Juicer</TH><TH>Cost</TH><TH>Image</TH>
                    </TR>
                    <xsl:for-each select="/juicers/juicer">
                        <TR>
                            <TD>
                                <A href="#{@id}-DESCRIPTION" name="{@id}-COST">
                                    <xsl:value-of select="name"/>
                                </A>
                            </TD>
                            <TD>
                                <xsl:text>$</xsl:text>
                                <xsl:value-of select="cost[@currency='USD']"/>
                            </TD>
                            <TD><IMG src="{image}" height="50" width="60"/></TD>
                        </TR>
                    </xsl:for-each>
                </TABLE>
                <br/><br/><br/><br/><br/><br/><br/>
                <br/><br/><br/><br/><br/><br/><br/>
                <br/><br/><br/><br/><br/><br/><br/>
                <br/><br/><br/><br/><br/><br/><br/>
                <TABLE BORDER="1" WIDTH="100%">
                    <TR>
                        <TH>Juicer</TH><TH>Description</TH>
                    </TR>
                    <xsl:for-each select="/juicers/juicer">
                        <TR>
                            <TD>
                                <A href="#{@id}-COST" name="{@id}-DESCRIPTION">
                                    <xsl:value-of select="name"/>
                                </A>
                            </TD>
                            <TD><xsl:value-of select="description"/></TD>
                        </TR>
                    </xsl:for-each>
                </TABLE>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>