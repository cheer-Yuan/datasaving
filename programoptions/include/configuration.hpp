#pragma once

// local headers

/** An interface providing access to the user-defined configuration.
 * 
 * Each configuration option is accessible through its own member function.
 */
class Configuration
{
public:
	// The destructor
	virtual ~Configuration() = default;
	
	/** Access the number of photos to take
	 * @return the number of photos to take
	 */
	virtual int give_photos() const = 0;

    /** Access the time interval between 2 images in seconds
    * @return time interval between 2 images in seconds
    */
    virtual int give_interval() const = 0;
	
	/** Access whether the normal rgb image will be saved
	 * @return whether the normal rgb image will be saved
	 */
	virtual int if_rgb() const = 0;
	
	/** Access whether the depth image will be saved
	 * @return whether the depth image will be saved
	 */
	virtual int if_depth() const = 0;
	
	/** Access whether the infra rouge image will be saved
	 * @return whether the infra rouge image will be saved
	 */
	virtual int if_infrarouge() const = 0;

    /** Access whether pointcloud will be generated in the .ply format
     * @return whether pointcloud will be generated in the .ply format
     */
    virtual int if_ply() const = 0;

    /** Access whether pointcloud will be generated with colors
    * @return whether pointcloud will be generated with colors
    */
    virtual int if_color() const = 0;

    /** Access whether use the lower resolution
    * @return whether use the lower resolution
    */
    virtual int if_lowres() const = 0;

};
