<?xml version="1.0" encoding="iso-8859-1"?>
<!--

 The contents of this file are subject to the Mozilla Public License Version
 1.1 (the "License"); you may not use this file except in compliance with
 the License. You may obtain a copy of the License at
 http://www.mozilla.org/MPL/
 
 Software distributed under the License is distributed on an "AS IS" basis,
 WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 for the specific language governing rights and limitations under the
 License.

mmTree - alternate XHTML+Javascript export style sheet for FreeMind.

 Miika Nurminen (minurmin@cc.jyu.fi) 12.12.2003.

Transforms Freemind (0.6.7 - 0.8.0) mm file to XHTML 1.1 with JavaScript-based keyboard navigation (MarkTree).
Output is valid (possibly apart HTML entered by user in Freemind).

Update (MN / 14.12.2004): 
 - Support for mm 0.7.1 - 0.8.0 constructs (clouds, internal links. opens internal link also if collapsed).
 - Support for icons. Some code adapted from Markus Brueckner's freemind2html.xsl style sheet.
 - newlines &#xa;&#xa; behaviour (find and convert to <br/>)

Todo:
 - Can CSS fonts be used with Freemind fonts?
 - Change licence to MIT -style.
 - integrate JS file to stylesheet
 - parameters: use_icons (true/false)
-->
<xsl:stylesheet version="1.0"
                xmlns="http://www.w3.org/1999/xhtml" 
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
>
<!-- mozilla doesn't parse method xhtml (in xslt 2.0) -->
<xsl:output method="xml"
            version="1.0"
            encoding="iso-8859-1"
            doctype-public="-//W3C//DTD XHTML 1.1//EN"  
            doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"
            omit-xml-declaration="no"
/>
<!-- fc, 17.10.2004: The following parameter is set by freemind. -->
<xsl:param name="destination_dir">./</xsl:param>

<!-- if true, external links urls are shown, default false. -->
<xsl:param name="show_link_url">false</xsl:param>

<!-- if true, shows standard freemind icons (assumed to be in ./icons directory -->
<xsl:param name="show_icons">true</xsl:param>

<xsl:strip-space elements="*"/>
<!-- note! nonempty links are required for opera! (tested with opera 7).
     #160 is non-breaking space.  / mn, 11.12.2003 
--><xsl:template match="/">
<xsl:processing-instruction name="xml-stylesheet">href="treestyles.css" type="text/css"</xsl:processing-instruction>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="fi" >
<head>
<title><xsl:value-of select="/map/node/@TEXT"/>
	</title>
	<xsl:element name="link"><xsl:attribute name="rel">stylesheet</xsl:attribute>
		<xsl:attribute name="href"><xsl:value-of select="$destination_dir"/>treestyles.css</xsl:attribute>
		<xsl:attribute name="type">text/css</xsl:attribute></xsl:element>
<xsl:element name="script"><xsl:attribute name="type">text/javascript</xsl:attribute>
	<xsl:attribute name="src"><xsl:value-of select="$destination_dir"/>marktree.js</xsl:attribute>&#160; </xsl:element>
</head>
<body>

<div class="basetop">
<a href="#" onclick="expandAll(document.getElementById('base'))">Expand</a> - <a href="#" onclick="collapseAll(document.getElementById('base'))">Collapse</a>
</div>
<div id="base" class="basetext">
<ul>

<xsl:apply-templates />

</ul>
</div>

</body>
</html>
</xsl:template>

<!-- line break handling -->
<xsl:template name="format_text">
  <xsl:param name="nodetext" />
<xsl:if test="string-length(substring-after($nodetext,'&#xa;&#xa;')) = 0">
  <xsl:value-of select="$nodetext" />
</xsl:if>
<xsl:if test="string-length(substring-after($nodetext,'&#xa;&#xa;')) &gt; 0">
  <xsl:value-of select="substring-before($nodetext,'&#xa;&#xa;')" />
<br />
          <xsl:call-template name="format_text">
             <xsl:with-param name="nodetext"><xsl:value-of select="substring-after($nodetext,'&#xa;&#xa;')" /></xsl:with-param>
          </xsl:call-template>
</xsl:if>
</xsl:template>

<xsl:template match="font"><xsl:if test="string-length(@SIZE) &gt; 0">font-size:<xsl:value-of select="round((number(@SIZE) div 12)*100)" />%;</xsl:if><xsl:if test="@BOLD='true'">font-weight:bold;</xsl:if><xsl:if test="@ITALIC='true'">font-style:italic;</xsl:if></xsl:template>


<xsl:template name="html">
    <xsl:choose>
        <xsl:when test="(substring(@TEXT,string-length(@TEXT)-13,14)='&lt;/body&gt;&lt;/html&gt;') and 
                                   (substring(@TEXT,1,12)='&lt;html&gt;&lt;body&gt;')">
         <xsl:value-of select="substring(@TEXT,13,string-length(@TEXT)-26)"  disable-output-escaping="yes"/>
        </xsl:when>              
        <xsl:when test="substring(@TEXT,string-length(@TEXT)-6,7)='&lt;/html&gt;'">
            <xsl:value-of select="substring(@TEXT,7,string-length(@TEXT)-14)"  disable-output-escaping="yes"/>
        </xsl:when>              
        <xsl:otherwise> 
            <xsl:value-of select="substring(@TEXT,7,string-length(@TEXT))"  disable-output-escaping="yes"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<xsl:template name="spantext">
  <xsl:element name="span">
    <xsl:attribute name="style">
       <xsl:if test="string-length(@COLOR) &gt; 0">color:<xsl:value-of select="@COLOR" />;
       </xsl:if>
       <xsl:apply-templates select="font" />
       </xsl:attribute>                    
<xsl:choose>
  <xsl:when test="(string-length(@LINK) &gt; 0) and (($show_link_url='false'))">
    <xsl:element name="a"><xsl:attribute name="href"> <xsl:value-of select="@LINK" /></xsl:attribute>
          <xsl:call-template name="format_text">
            <xsl:with-param name="nodetext"><xsl:value-of select="@TEXT" /></xsl:with-param>
          </xsl:call-template>
    </xsl:element>
<xsl:if test="$show_icons='true'">
<xsl:text> </xsl:text>
    <xsl:element name="a"><xsl:attribute name="href"> <xsl:value-of select="@LINK" /></xsl:attribute><xsl:element name="img">
          <xsl:attribute name="src"><xsl:value-of select="$destination_dir"/>icons/Link.png</xsl:attribute>
          <xsl:attribute name="alt"><xsl:value-of select="@BUILTIN" /></xsl:attribute>
          <xsl:attribute name="style">border-width:0</xsl:attribute>
        </xsl:element>
</xsl:element>
</xsl:if>

    </xsl:when>
<xsl:otherwise>
          <xsl:call-template name="format_text">
            <xsl:with-param name="nodetext"><xsl:value-of select="@TEXT" /></xsl:with-param>
          </xsl:call-template>
</xsl:otherwise>
 </xsl:choose>

  </xsl:element>

  <xsl:if test="(string-length(@LINK) &gt; 0) and (($show_link_url='true'))">
    - [ <a><xsl:attribute name="href"><xsl:value-of select="@LINK" />  
    </xsl:attribute><xsl:value-of select="@LINK"/></a> ]   
  </xsl:if>

    <xsl:if test="string-length(normalize-space(@TEXT)) = 0">
      <br /> <!-- anonymous node -->
    </xsl:if>
</xsl:template>


<xsl:template match="node">
<!--  <xsl:choose>
  <xsl:when test="(string-length(normalize-space(@TEXT)) = 0) and (string-length(normalize-space(@LINK))= 0)">      
    <xsl:if test="count(child::node)=0"> 
          <xsl:call-template name="listnode">
            <xsl:with-param name="lifold">basic</xsl:with-param>
          </xsl:call-template>
    </xsl:if>
    <xsl:if test="count(child::node)>0" > 
      <xsl:choose>
        <xsl:when test="@FOLDED='true'">
          <xsl:call-template name="listnode">
            <xsl:with-param name="lifold">exp</xsl:with-param>
            <xsl:with-param name="ulfold">sub</xsl:with-param>
          </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
          <xsl:call-template name="listnode">
            <xsl:with-param name="lifold">col</xsl:with-param>
            <xsl:with-param name="ulfold">subexp</xsl:with-param>
          </xsl:call-template>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>

     <xsl:if test="count(child::node)>0" > - anonoymous nodes are not processed, but their children are -
       <xsl:apply-templates select="node" />  
     </xsl:if>
     <xsl:if test="count(child::node)=0" >
       <li class="basic" /> - must be here to render valid html -
     </xsl:if>
  </xsl:when>
  <xsl:when test="(string-length((@TEXT)) > 0) or (string-length(@LINK) > 0)">      -->
    <xsl:if test="count(child::node)=0"> 
          <xsl:call-template name="listnode">
            <xsl:with-param name="lifold">basic</xsl:with-param>
          </xsl:call-template>
    </xsl:if>
    <xsl:if test="count(child::node)>0" > 
      <xsl:choose>
        <xsl:when test="@FOLDED='true'">
          <xsl:call-template name="listnode">
            <xsl:with-param name="lifold">exp</xsl:with-param>
            <xsl:with-param name="ulfold">sub</xsl:with-param>
          </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
          <xsl:call-template name="listnode">
            <xsl:with-param name="lifold">col</xsl:with-param>
            <xsl:with-param name="ulfold">subexp</xsl:with-param>
          </xsl:call-template>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>
<!--</xsl:when>
<xsl:otherwise>
  <xsl:apply-templates select="node" />
</xsl:otherwise>
</xsl:choose>-->
</xsl:template>


<xsl:template name="listnode">
  <xsl:param name="lifold" />
  <xsl:param name="ulfold" />
          <li class="{$lifold}">     

<xsl:attribute name="style">
       <xsl:if test="string-length(cloud/@COLOR) &gt; 0">background-color:<xsl:value-of select="cloud/@COLOR" />;
       </xsl:if>
</xsl:attribute>
      <!-- check if this node has an ID (for the document internal links) -->
      <xsl:if test="@ID">
        <!-- note: as FreeMind sometimes prepends the IDs with an underscore which is not valid
                   as the first character in an HTML id, we surround the ID with FM<ID>FM -->
        
        <xsl:attribute name="id">FM<xsl:value-of select="@ID"/>FM</xsl:attribute>
  
      </xsl:if>

<xsl:if test="$show_icons='true'">
<xsl:for-each select="icon">
        <xsl:element name="img">
          <xsl:attribute name="src"><xsl:value-of select="$destination_dir"/>icons/<xsl:value-of select="@BUILTIN" />.png</xsl:attribute>
          <xsl:attribute name="alt"><xsl:value-of select="@BUILTIN" /></xsl:attribute>
        </xsl:element>
<xsl:text> </xsl:text>
      </xsl:for-each>
</xsl:if> 

            <xsl:choose>        
            <xsl:when test="substring(@TEXT,1,6)='&lt;html&gt;'">
              <xsl:call-template name="html" />
            </xsl:when>
            <xsl:otherwise>
              <xsl:call-template name="spantext" />
            </xsl:otherwise>
            </xsl:choose>
            <xsl:if test="count(child::node)>0"> 
              <ul class="{$ulfold}"><xsl:apply-templates select="node"/></ul>
            </xsl:if>

      <!-- if there are arrowlinks inside this node (i.e. this node is connected to another node
           in FreeMind using an arrow), then create a document internal link -->
<xsl:if test="count(child::arrowlink) &gt; 0">
<xsl:if test="$show_icons='false'">
 - [
</xsl:if>

      <xsl:for-each select="arrowlink">
       <xsl:text> </xsl:text> <a>
          <xsl:attribute name="onclick">getVisibleParents('FM<xsl:value-of select="@DESTINATION" />FM')</xsl:attribute>
          <xsl:attribute name="href">#FM<xsl:value-of select="@DESTINATION" />FM</xsl:attribute>
<xsl:if test="$show_icons='true'">
					<xsl:element name="img">
						<xsl:attribute name="src"><xsl:value-of select="$destination_dir"/>ilink.png</xsl:attribute>
						<xsl:attribute name="class">ilink</xsl:attribute>
						<xsl:attribute name="alt">Internal Link</xsl:attribute>
					</xsl:element>
</xsl:if>
<xsl:if test="$show_icons='false'">
link
</xsl:if>
        </a>
      </xsl:for-each>
<xsl:if test="$show_icons='false'">
 ]
</xsl:if>
</xsl:if>
  </li>
</xsl:template>

</xsl:stylesheet>
