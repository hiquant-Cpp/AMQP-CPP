/**
 *  Class describing a basic QOS frame
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
class BasicQosFrame : public BasicFrame
{
private:
        /**
         *  specifies the size of the prefetch window in octets
         *  @var int32_t
         */
        int32_t _prefetchSize;

        /**
         *  specifies a prefetch window in terms of whole messages
         *  @var int16_t
         */
        int16_t _prefetchCount;

        /**
         *  apply QoS settings to entire connection
         *  @var BooleanSet
         */
        BooleanSet _global;
protected:
    /**
     * Encode a frame on a string buffer
     *
     * @param   buffer  buffer to write frame to
     */
    virtual void fill(OutBuffer& buffer) const override
    {
        // call base
        BasicFrame::fill(buffer);

        // add fields
        buffer.add(_prefetchSize);
        buffer.add(_prefetchCount);
        _global.fill(buffer);
    }

public:
    /**
     *  Destructor
     */
    virtual ~BasicQosFrame() {}
    /**
     * Construct a basic qos frame
     *
     * @param   channel         channel we're working on
     * @param   prefetchSize    specifies the size of the prefetch window in octets
     * @param   prefetchCount   specifies a prefetch window in terms of whole messages
     * @param   global          apply QoS settings to entire connection
     * @default false
     */
    BasicQosFrame(uint16_t channel, int32_t prefetchSize = 0, int16_t prefetchCount = 0, bool global = false) :
        BasicFrame(channel, 7), // 4 (int32) + 2 (int16) + 1 (bool)
        _prefetchSize(prefetchSize),
        _prefetchCount(prefetchCount),
        _global(global)
    {}


    BasicQosFrame(ReceivedFrame &frame) :
        BasicFrame(frame),
        _prefetchSize(frame.nextInt32()),
        _prefetchCount(frame.nextInt16()),
        _global(frame)
    {}

    /**
     * Return the method ID
     * @return  uint16_t
     */
    uint16_t methodID() const
    {
        return 10;
    }

    /**
     * Return the prefetch count
     * @return int16_t
     */
    int16_t prefetchCount() const
    {
        return _prefetchCount;
    }

    /**
     * returns the value of global
     * @return  boolean
     */
    bool global() const
    {
        return _global.get(0);
    }

    /**
     *  returns the prefetch size
     *  @return int32_t
     */
    int32_t prefetchSize() const
    {
        return _prefetchSize;
    }
};

/**
 *  End namespace
 */
}

