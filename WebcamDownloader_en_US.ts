<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="en">
<context>
    <name>Help</name>
    <message>
        <location filename="Help.qml" line="10"/>
        <source>window-title-help</source>
        <translation>How To Use</translation>
    </message>
    <message>
        <location filename="Help.qml" line="22"/>
        <source>text-how-to-use</source>
        <translation>&lt;h1&gt;How to use&lt;/h1&gt;

&lt;p&gt;This section describes how to use this app to download videos.&lt;/p&gt;

&lt;h2&gt;Adding models&lt;/h2&gt;
&lt;p&gt;
    At the top of the window select your preferred webcam host, in the field to the right write either the
    username of the model or the website address for the model and click &lt;b&gt;Add&lt;/b&gt;.
&lt;/p&gt;

&lt;p&gt;
    If you did everything correctly, the model&apos;s name should now be visible in the &lt;b&gt;Saved models&lt;/b&gt;
    section.
&lt;/p&gt;

&lt;h2&gt;Downloading&lt;/h2&gt;
&lt;p&gt;
    In the &lt;b&gt;Saved models&lt;/b&gt; section tick the &lt;b&gt;Download&lt;/b&gt; checkbox for every model that you want
    to start downloading. If the model is not online, the checkbox cannot be ticked.
    Afterwards click the &lt;b&gt;Download&lt;/b&gt; button on the right.
&lt;/p&gt;
&lt;p&gt;
    To stop downloading either select the &lt;b&gt;Stop All Downloads&lt;/b&gt; button or untick the &lt;b&gt;Download&lt;/b&gt;
    checkbox for the models you don&apos;t want to download and press the &lt;b&gt;Download&lt;/b&gt; button.
&lt;/p&gt;
&lt;p&gt;
    &lt;b&gt;The Download button starts downloading all checked models and stops downloading all unchecked
    models.&lt;/b&gt; It may be a little confusing at first, but basically it checks what models that aren&apos;t
    currently being downloaded it should download and what models that are being downloaded it should
    stop downloading.
&lt;/p&gt;

&lt;h2&gt;Automatic downloading&lt;/h2&gt;
&lt;p&gt;
    The automatic downloading serves to download the model whenever they get online.
    To start automatic downloads of a model, check the &lt;b&gt;Auto Download&lt;/b&gt; checkbox and click the
    &lt;b&gt;Enable Autodownloads&lt;/b&gt; button. If you instead see the &lt;b&gt;Disable Autodownloads&lt;/b&gt; button
    it means automatic downloads are already enabled.
&lt;/p&gt;
&lt;p&gt;
    To stop automatic downloading just uncheck the &lt;b&gt;Auto Download&lt;/b&gt; checkbox for the model.
    It may take up to 10 seconds before the download is stopped if it&apos;s currently downloading.
    Another option is to click the &lt;b&gt;Stop All Downloads&lt;/b&gt; button.
    &lt;b&gt;If you click it, automatic downloads will be disabled, you need to enable them again
    if you want to resume automatic downloads.&lt;/b&gt;
&lt;/p&gt;

&lt;h2&gt;Settings&lt;/h2&gt;
&lt;p&gt;
    Go to the &lt;b&gt;Options -&gt; Settings&lt;/b&gt; menu to configure the application.
&lt;/p&gt;
&lt;ul&gt;
    &lt;li&gt;
        &lt;b&gt;Close to system tray?&lt;/b&gt; - this option allows you to hide the app in system tray
        when you close it; most useful in combination with automatic downloads, this way it won&apos;t
        be visible among your active apps but will continue to work in background and can be opened
        any time from the system tray (usually next to your clock)
    &lt;/li&gt;
    &lt;li&gt;
        &lt;b&gt;Check for new versions?&lt;/b&gt; - if enabled, the app will check for new versions of this app
        and offer you to download it
    &lt;/li&gt;
    &lt;li&gt;
        &lt;b&gt;Downloads Folder&lt;/b&gt; - this speaks for itself, you can change where the recordings are
        downloaded to. By default it&apos;s your system Downloads folder
    &lt;/li&gt;
&lt;/ul&gt;

&lt;h2&gt;Console mode&lt;/h2&gt;
&lt;p&gt;
    The app can be ran in console mode without user interface. To see usage help run the app from
    command line with argument &lt;code&gt;help&lt;/code&gt;.
&lt;/p&gt;
&lt;p&gt;
    &lt;i&gt;Note: Currently doesn&apos;t support downloading from command line, only model management.&lt;/i&gt;
&lt;/p&gt;</translation>
    </message>
</context>
<context>
    <name>Settings</name>
    <message>
        <location filename="Settings.qml" line="10"/>
        <source>window-title-settings</source>
        <oldsource>menu-settings</oldsource>
        <translation>Settings</translation>
    </message>
    <message>
        <location filename="Settings.qml" line="22"/>
        <source>option-close-to-tray</source>
        <translation>Close to system tray?</translation>
    </message>
    <message>
        <location filename="Settings.qml" line="28"/>
        <location filename="Settings.qml" line="57"/>
        <source>yes</source>
        <translation>Yes</translation>
    </message>
    <message>
        <location filename="Settings.qml" line="28"/>
        <location filename="Settings.qml" line="57"/>
        <source>no</source>
        <translation>No</translation>
    </message>
    <message>
        <location filename="Settings.qml" line="51"/>
        <source>option-check-for-new-versions</source>
        <translation>Check for new versions?</translation>
    </message>
    <message>
        <location filename="Settings.qml" line="80"/>
        <source>option-download-directory</source>
        <translation>Downloads Folder</translation>
    </message>
    <message>
        <location filename="Settings.qml" line="94"/>
        <source>button-browse-files</source>
        <translation>Browse</translation>
    </message>
</context>
<context>
    <name>main</name>
    <message>
        <location filename="main.qml" line="24"/>
        <source>app-title</source>
        <translation>Webcam Downloader</translation>
    </message>
    <message>
        <location filename="main.qml" line="35"/>
        <source>menu-help</source>
        <translation>Help</translation>
    </message>
    <message>
        <location filename="main.qml" line="223"/>
        <location filename="main.qml" line="500"/>
        <source>error-model-not-found</source>
        <translation>Model with that name was not found</translation>
    </message>
    <message>
        <location filename="main.qml" line="193"/>
        <source>placeholder-model-name</source>
        <translation>Model name or URL</translation>
    </message>
    <message>
        <location filename="main.qml" line="28"/>
        <source>menu-options</source>
        <translation>Options</translation>
    </message>
    <message>
        <location filename="main.qml" line="30"/>
        <source>menu-settings</source>
        <translation>Settings</translation>
    </message>
    <message>
        <location filename="main.qml" line="37"/>
        <source>menu-how-to-use</source>
        <oldsource>menu-settings</oldsource>
        <translation>How to use</translation>
    </message>
    <message>
        <location filename="main.qml" line="158"/>
        <source>title-new-version-found</source>
        <translation>New Version Found!</translation>
    </message>
    <message>
        <location filename="main.qml" line="166"/>
        <source>text-new-version-found</source>
        <translation>New version (%1) found, do you want to download it now?</translation>
    </message>
    <message>
        <location filename="main.qml" line="198"/>
        <source>fetch-info-button-text</source>
        <translation>Add</translation>
    </message>
    <message>
        <location filename="main.qml" line="211"/>
        <source>label-models</source>
        <translation>Saved models</translation>
    </message>
    <message>
        <location filename="main.qml" line="252"/>
        <source>table-header-model-name</source>
        <translation>Model name</translation>
    </message>
    <message>
        <location filename="main.qml" line="258"/>
        <source>table-header-friendly-hostname</source>
        <translation>Website</translation>
    </message>
    <message>
        <location filename="main.qml" line="264"/>
        <source>table-header-status</source>
        <translation>Status</translation>
    </message>
    <message>
        <location filename="main.qml" line="270"/>
        <source>table-header-download</source>
        <translation>Download</translation>
    </message>
    <message>
        <location filename="main.qml" line="277"/>
        <source>table-header-auto-download</source>
        <translation>Auto Download</translation>
    </message>
    <message>
        <location filename="main.qml" line="284"/>
        <location filename="main.qml" line="366"/>
        <source>table-header-delete</source>
        <translation>Delete</translation>
    </message>
    <message>
        <location filename="main.qml" line="387"/>
        <source>status-downloading</source>
        <translation>Downloading</translation>
    </message>
    <message>
        <location filename="main.qml" line="394"/>
        <source>status-online</source>
        <translation>Online</translation>
    </message>
    <message>
        <location filename="main.qml" line="397"/>
        <source>status-offline</source>
        <translation>Offline</translation>
    </message>
    <message>
        <location filename="main.qml" line="479"/>
        <source>button-open-downloads</source>
        <translation>Open Downloads Folder</translation>
    </message>
    <message>
        <location filename="main.qml" line="313"/>
        <location filename="main.qml" line="401"/>
        <source>status-unknown</source>
        <translation>Unknown</translation>
    </message>
    <message>
        <location filename="main.qml" line="52"/>
        <source>tray-quit</source>
        <translation>Quit</translation>
    </message>
    <message>
        <location filename="main.qml" line="417"/>
        <source>label-actions</source>
        <translation>Actions</translation>
    </message>
    <message>
        <location filename="main.qml" line="426"/>
        <source>button-start-downloads</source>
        <translation>Download</translation>
    </message>
    <message>
        <location filename="main.qml" line="447"/>
        <source>button-stop-all-downloads</source>
        <translation>Stop All Downloads</translation>
    </message>
    <message>
        <location filename="main.qml" line="470"/>
        <source>button-disable-autodownloads</source>
        <translation>Disable Autodownloads</translation>
    </message>
    <message>
        <location filename="main.qml" line="471"/>
        <source>button-enable-autodownloads</source>
        <translation>Enable Autodownloads</translation>
    </message>
</context>
</TS>
