<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Welcome</TITLE>
            </HEAD>
            <BODY>
                <TABLE border="1" width="25%">
                    <TR><TH>Name</TH></TR>
                    <xsl:for-each select="/FitnessCenter/Member">
                        <TR>
                            <TD> <!--一个连接 引用到下面的name上-->
                                <A href="#{@id}">
                                    <xsl:value-of select="Name"/>
                                </A>
                            </TD>
                        </TR>
                    </xsl:for-each>
                </TABLE>
                <BR/><BR/><BR/><BR/><BR/>
                <BR/><BR/><BR/><BR/><BR/>
                <BR/><BR/><BR/><BR/><BR/>
                <BR/><BR/><BR/><BR/><BR/>
                <BR/><BR/><BR/><BR/><BR/>
                <TABLE border="1" width="25%">
                    <TR><TH>Home Phone Number</TH></TR>
                    <xsl:for-each select="/FitnessCenter/Member">
                        <TR>
                            <TD>  <!--名字引用-->
                                <A name="{@id}">
                                    <xsl:value-of select="Phone[@type='home']"/>
                                </A>
                            </TD>
                        </TR>
                    </xsl:for-each>
                </TABLE>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>