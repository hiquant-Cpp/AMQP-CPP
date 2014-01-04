/**
 *  Class describing connection vhost open frame
 * 
 *  This frame is sent by the client after the connection is started and the
 *  capacity has been tuned, to open the connection to a specific vhost.
 * 
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace AMQP {

/**
 *  Class implementation
 */
class ConnectionOpenFrame : public ConnectionFrame
{
private:
    /**
     *  Virtual host name
     *  @var ShortString
     */
    ShortString _vhost;

    /**
     *  deprecated values, still need to read them somehow in the constructor
     *  @var ShortString
     */
    ShortString _deprecatedCapabilities;
    
    /**
     *  More deprecated values
     *  @var BooleanSet
     */
    BooleanSet  _deprecatedInsist;

protected:
    /**
     *  Encode a frame on a string buffer
     *
     *  @param  buffer  buffer to write frame to
     */
    virtual void fill(OutBuffer& buffer) const override
    {
        // call base
        ConnectionFrame::fill(buffer);

        // encode fields
        _vhost.fill(buffer);
        _deprecatedCapabilities.fill(buffer);
        _deprecatedInsist.fill(buffer);
    }

public:
    /**
     *  Open a virtual host
     *
     *  @param  vhost   name of virtual host to open
     */
    ConnectionOpenFrame(const std::string &vhost) :
        ConnectionFrame(vhost.length() + 3), // length of vhost + byte to encode this length + deprecated shortstring size + deprecated bool
        _vhost(vhost),
        _deprecatedCapabilities(""),
        _deprecatedInsist()
    {}

     /**
     *  Constructor based on a received frame
     *
     *  @param  frame   received frame
     */
    ConnectionOpenFrame(ReceivedFrame &frame) :
        ConnectionFrame(frame),
        _vhost(frame),
        _deprecatedCapabilities(frame),
        _deprecatedInsist(frame)
    {}

    /**
     *  Destructor
     */
    virtual ~ConnectionOpenFrame() {}

    /**
     *  Method id
     */
    uint16_t methodID() const
    {
        return 40;
    }

    /**
     *  Get the vhost name
     *  @return string
     */
    const std::string& vhost() const
    {
        return _vhost;
    }
};

/**
 *  end namespace
 */
}

