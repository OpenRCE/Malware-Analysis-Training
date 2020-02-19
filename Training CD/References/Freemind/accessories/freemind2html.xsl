<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

  <!--
       File:        freemind.xsl
       Version:     0.1
       Description: A XSLT stylesheet to transform mindmap files created with FreeMind (http://freemind.sf.net)
                    into HTML files. The transformation will keep the structure of the files, clouds (with it's colors),
                    icons, internal and external links and the ability to collapse whole subtrees of the document (with
                    JavaScript enabled).
                    The results of the transformation were tested and found to be working in the following browsers:
                    -Internet Explorer 6
                    -Mozilla Firefox 0.9 (should be working with nearly any browser using the Geko engine)
                    -Konqueror
                    -Opera 7
                    Other browsers were not tested, but you should have a good chance of gettting things to work
                    with them.
       Usage:       Use any XSLT-Processor (development was done using xsltproc under Linux) to apply this stylesheet
                    to the FreeMind-file. Copy the result and all the PNG-Files inside the script directory
                    (including the icons-subdir) into a directory of it's own (e.g. on a webserver).
                    Open the HTML-file with a webbrowser.
       Author:      Markus Brueckner <freemind-xsl@slash-me.net>
       License:     BSD license without advertising clause. (see http://www.opensource.org/licenses/bsd-license.php
                     for further details)
  -->

  <xsl:output method="html" doctype-public="-//W3C//DTD HTML 4.01 Strict//EN" 
    doctype-system="http://www.w3.org/TR/html4/strict.dtd"/>

<!-- fc, 20.10.2004: The following parameter is set by freemind. -->
<xsl:param name="destination_dir">./</xsl:param>
<xsl:param name="area_code"></xsl:param>
<xsl:param name="folding_type">html_export_no_folding</xsl:param>
	<!-- possible values: 
		html_export_fold_all, 
		html_export_no_folding, 
		html_export_fold_currently_folded, 
		html_export_based_on_headings: this means, that approx. five levels are given, more deeper nodes are folded.
		As of the time being, this parameter is not used.
		-->

  <xsl:template match="/">
    <html>
      <head>
        <!-- look if there is any node inside the map (there should never be none, but who knows?) 
             and take its text as the title -->
        <xsl:choose>
          <xsl:when test="/map/node">
            <title><xsl:value-of select="/map/node/@TEXT" /></title>
          </xsl:when>
          <xsl:otherwise>
            <title>FreeMind2HTML Mindmap</title>
          </xsl:otherwise>
        </xsl:choose>
        <!-- Stylesheet, generator and some JavaScript for the collapsing of the trees -->
 	<xsl:element name="link"><xsl:attribute name="rel">stylesheet</xsl:attribute>
		<xsl:attribute name="href"><xsl:value-of select="$destination_dir"/>freemind2html.css</xsl:attribute>
		<xsl:attribute name="type">text/css</xsl:attribute></xsl:element>
        <meta name="generator" content="FreeMind-XSL Stylesheet (see: http://freemind-xsl.dev.slash-me.net/ for details)" />
			<xsl:element name="script"><xsl:attribute name="type">text/javascript</xsl:attribute>
				<xsl:attribute name="src"><xsl:value-of select="$destination_dir"/>freemind2html.js</xsl:attribute>&#160; 
			</xsl:element>
      <script type="text/javascript">
          <![CDATA[
          <!--
               function toggle(id)
               {
                   div_el = document.getElementById(id);
                   img_el = document.getElementById('img'+id);
                   if (div_el.style.display != 'none')
                   {
          ]]>
					
                      div_el.style.display='none';
                      img_el.src = '<xsl:value-of select="$destination_dir"/>show.png';
          <![CDATA[
                   }
                   else
                   {
          ]]>
                      div_el.style.display='block';
                      img_el.src = '<xsl:value-of select="$destination_dir"/>hide.png';
          <![CDATA[
                   };
               };
           -->
          ]]>
        </script>
      </head>
		<body>
			<!-- choose the first nodes text again as the headline -->
			<h1>
				<xsl:choose>
					<xsl:when test="/map/node">
						<xsl:value-of select="/map/node/@TEXT" />
					</xsl:when>
					<xsl:otherwise> FreeMind2HTML Mindmap </xsl:otherwise>
				</xsl:choose>
			</h1>
			<!-- place image -->
			<div style="width:96%; 	padding:2%; 	margin-bottom:10px; 	border: 0px; 	text-align:center; 	vertical-align:center;">
					<xsl:element name="img">
						<xsl:attribute name="src"><xsl:value-of select="$destination_dir"/>image.png</xsl:attribute>
						<xsl:attribute name="style">margin-bottom:10px; 	border: 0px; 	text-align:center; 	vertical-align:center;</xsl:attribute>
						<xsl:attribute name="alt">Imagemap</xsl:attribute>
						<xsl:attribute name="usemap">#fm_imagemap</xsl:attribute>
					</xsl:element>
			</div>
			<map name="fm_imagemap" id="fm_imagemap">
				<xsl:value-of select="$area_code" disable-output-escaping="yes"/>
			</map>
			<xsl:apply-templates />
		</body>
    </html>
  </xsl:template>

  <!-- the template to output for each node -->
  <xsl:template match="node">
    <div>
      <!-- generate a unique ID that can be used to reference this node e.g. from the JavaScript -->
      <xsl:variable name="contentID">
          <xsl:value-of select="generate-id()"/>
      </xsl:variable>
      <!-- check whether this node is a cloud... -->
      <xsl:choose>
        <xsl:when test="cloud">
          <!-- ...if yes, check whether it has a special color... -->
          <xsl:choose>
            <xsl:when test="cloud/@COLOR">
              <xsl:attribute name="class">cloud</xsl:attribute>
              <xsl:attribute name="style">background-color: <xsl:value-of select="cloud/@COLOR" /></xsl:attribute>
            </xsl:when>
            <!-- no? Then choose some default color -->
            <xsl:otherwise>
              <xsl:attribute name="class">cloud</xsl:attribute>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:when>
        <xsl:otherwise>
          <xsl:attribute name="class">node</xsl:attribute>
        </xsl:otherwise>
      </xsl:choose>
      <!-- check whether this node has any child nodes... -->
      <xsl:choose>
        <xsl:when test="node">
          <!-- ...yes? Then put the "hide" button in front of the text... -->
          <!--<img src="hide.png" class="hideshow" alt="hide">-->
					<xsl:element name="img">
						<xsl:attribute name="src"><xsl:value-of select="$destination_dir"/>hide.png</xsl:attribute>
						<xsl:attribute name="class">hideshow</xsl:attribute>
						<xsl:attribute name="alt">hide</xsl:attribute>
            <xsl:attribute name="onClick"><![CDATA[toggle("]]><xsl:value-of select="$contentID" /><![CDATA[")]]></xsl:attribute>
            <xsl:attribute name="id">img<xsl:value-of select="$contentID" /></xsl:attribute>
					</xsl:element>
					<!--</img>-->
        </xsl:when>
        <xsl:otherwise>
          <!-- ...no? Then output the empty leaf icon -->
          <!--<img src="leaf.png" class="hideshow" alt="leaf" />-->
					<xsl:element name="img">
						<xsl:attribute name="src"><xsl:value-of select="$destination_dir"/>leaf.png</xsl:attribute>
						<xsl:attribute name="class">hideshow</xsl:attribute>
						<xsl:attribute name="alt">leaf</xsl:attribute>
					</xsl:element>
        </xsl:otherwise>
      </xsl:choose>
      <!-- when there are icons for this node then output the according <img>-tags -->
      <xsl:for-each select="icon">
        <img>
          <xsl:attribute name="src"><xsl:value-of select="$destination_dir"/>icons/<xsl:value-of select="@BUILTIN" />.png</xsl:attribute>
          <xsl:attribute name="alt"><xsl:value-of select="@BUILTIN" /></xsl:attribute>
        </img>
      </xsl:for-each>
      <!-- check if this node has an ID (for the document internal links) -->
      <xsl:if test="@ID">
        <!-- note: as FreeMind sometimes prepends the IDs with an underscore which is not valid
                   as the first character in an HTML id, we surround the ID with FM<ID>FM -->
        <a>
          <xsl:attribute name="id">FM<xsl:value-of select="@ID"/>FM</xsl:attribute>
        </a>
      </xsl:if>
      <!-- check whether this node has a link-ID (for external URLs) -->
      <xsl:choose>
        <xsl:when test="@LINK">
          <a>
            <xsl:attribute name="href">
              <xsl:value-of select="@LINK" />
            </xsl:attribute>
		   <xsl:apply-templates select="." mode="textOut"/>
          </a>
        </xsl:when>
        <xsl:otherwise>
		   <xsl:apply-templates select="." mode="textOut"/>
        </xsl:otherwise>
      </xsl:choose>
      <!-- if there are arrowlinks inside this node (i.e. this node is connected to another node
           in FreeMind using an arrow), then create a document internal link -->
      <xsl:for-each select="arrowlink">
        <a>
          <xsl:attribute name="href">#FM<xsl:value-of select="@DESTINATION" />FM</xsl:attribute>
					<!--          <img src="ilink.png" alt="Internal Link" class="ilink" />
						-->
					<xsl:element name="img">
						<xsl:attribute name="src"><xsl:value-of select="$destination_dir"/>ilink.png</xsl:attribute>
						<xsl:attribute name="class">ilink</xsl:attribute>
						<xsl:attribute name="alt">Internal Link</xsl:attribute>
					</xsl:element>
        </a>
      </xsl:for-each>
		<!-- Output the note.-->
	 <xsl:apply-templates select="hook" mode="notes"/>
      <!-- the content div. This div contains all subnodes of this node. It carries the unique ID
           created in the beginning (which is used to hide this div when necessary). The content node
           is only created if there are any subnodes -->
      <xsl:if test="node">        
      <div class="content">
        <xsl:attribute name="id">
          <xsl:value-of select="$contentID" />
        </xsl:attribute>
        <xsl:apply-templates select="node"/>
      </div>
      </xsl:if>
    </div>
  </xsl:template>

	<xsl:template match="hook[@NAME='accessories/plugins/NodeNote.properties']" mode="notes">
		<xsl:choose>
			<xsl:when test="./text">
				<br/>
				<p class="notes">
					<xsl:call-template name="notesOut">
						<xsl:with-param name="text"><xsl:value-of select="./text"/></xsl:with-param>
					</xsl:call-template>
				</p>
			</xsl:when>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="notesOut">
		<xsl:param name="text"></xsl:param><!--
	 --><xsl:value-of select="$text"/><!--
--></xsl:template>
	
	<xsl:template match="node" mode="textOut">
		<xsl:choose>
			<xsl:when
				test="starts-with(@TEXT, '&lt;html&gt;&lt;img src=&quot;')">
				<xsl:variable name="file"><xsl:value-of
						select="substring-before(substring(@TEXT, 17), '&quot;')"/>
					</xsl:variable>
				<xsl:element name="a"><xsl:attribute name="href"><xsl:value-of
						select="$file"/></xsl:attribute>
					<xsl:element name="img">
						<xsl:attribute name="class">images</xsl:attribute>
						<xsl:attribute name="src">
							<xsl:value-of select="$file"/>
						</xsl:attribute>
					</xsl:element></xsl:element>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="@TEXT" />
			</xsl:otherwise>
		</xsl:choose>

	</xsl:template>	

</xsl:stylesheet>
